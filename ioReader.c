#include "ioReader.h"
#include "page.h"


void read_page_terms(Page* page, char * dir, ST * stop_words, ST * term_list);

ST * read_stop_words(char * dir){
    ST * stop_words = ST_init();
    
    char * dir_name =  define_directory_path(dir, "/stopwords.txt");
    //print_char(dir_name);
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(dir_name);

    char string[STRING_SZ];
    int i = 0;

    // arrumar essa leitura
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        String * str_ptr = string_create(string);
        int sucess=ST_PUT(stop_words, str_ptr, str_ptr);
        if (!sucess)
            string_destroy(str_ptr);
        i++;
    }


    fclose(fp);

    return stop_words;
}



StringMapVector * read_pages_name( char * dir){
    
    StringMapVector * smv = SMV_create(page_destroy); 

    char * dir_name =  define_directory_path(dir, "/index.txt");
    
    FILE * fp = fopen(dir_name,"r");
    free(dir_name);

    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }

    char string[STRING_SZ];
    int i = 0;
    // arrumar essa leitura
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        String * page_name = string_create(string);

        Page * page = page_create(page_name);
        //printf("PAGE NAME : ");
        //string_print(page_name);
        SMV_insert(smv, page, page_name);
        i++;
    }

    fclose(fp);

    return smv;


}

ST * read_terms(char * dir,  StringMapVector * pages, ST * stop_words){
    ST * term_list = ST_init();

    int i = 0;
    //printf("Leitura do conteudo das paginas\n"); //debug
    for(int i = 0; i < SMV_get_size(pages); i ++){
        //printf("Page %d: ", i);
        Page * page = SMV_get_by_idx(pages, i);
        //string_print_v2(page_get_name(page));
        //printf("\n");
        
        read_page_terms(page, dir, stop_words, term_list);
        //printf("\n\n");
    }

    
    return term_list;
}


void read_page_terms(Page * page, char * dir, ST * stop_words, ST * term_list){

    // VERIFICAR SE TA INSERINDO DE ACORDO COM AS CONDIÇOES DO PDF!
    
    String * page_name = page_get_name(page);
    char * tmp =  define_directory_path(dir, "/pages/");
    char * file_path = define_directory_path(tmp, string_get_char_pointer(page_name,0));
    free(tmp);

    //print_char(file_path);
    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
     
    char c;
    char string[STRING_SZ];
    while(fscanf(fp,"%199s%c", string, &c) != EOF){
        String * term = string_create(string); 
        string_tolower(term);

        Vector * vet_term_docs = NULL;

        if(!ST_get(stop_words, term)){ // nao eh uma stop word
            if(vet_term_docs = ST_get(term_list, term)){
                Page * last_page = vector_get_last(vet_term_docs);

                String * last_page_name = page_get_name(last_page);
                if(last_page_name != NULL){
                    if(compare(page_name,last_page_name) != 0){ // Nao eh igual
                        vector_insert(vet_term_docs, page); // insere o documento cmo associado ao termo
                    }
                }
            }
            else {
                // cria um vetor de documentos novo
                vet_term_docs = vector_create(VECTOR_SZ, NULL);
                vector_insert(vet_term_docs, page); // insere o documento cmo associado ao termo
                ST_PUT(term_list, term, vet_term_docs);
            }

            page_insert_word(page, term);// talvez p reduzir memoria reaproveitar o ponteiro
        }
        else{
            // eh uma stopword
            //printf("era stop word:");
            //string_print(term);
            string_destroy(term);
        }
    }
    
    fclose(fp);

}

void read_pages_graph(char * dir, StringMapVector * pages){
    
    //printf("\n\n\nPAGE LINKS:\n\n\n"); 

    char * file_path =  define_directory_path(dir, "/graph.txt");

    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
    
    char string[STRING_SZ]; 

    
    // arrumar essa leitura
    while(fscanf(fp,"%[^\n\t ]", string) != EOF){
        fscanf(fp,"%*[\n\t ]");
        String * vertex = string_create(string); // nome do arquivo (vertice)
        
        int n; // numero de elementos associados
        fscanf(fp,"%d", &n);
        fscanf(fp,"%*[ ]");

        
        Page * page = SMV_get_by_key(pages, vertex); 
        page_set_out_number(page, n);


        for(int i = 0 ; i < n; i++){
            fscanf(fp,"%[^ \n\t]", string);
            fscanf(fp,"%*[ \n\t]");
            
            String * adj_vertex = string_create(string); // nome do arquivo adjacentes ao vertex 

            Page * page_adj = SMV_get_by_key(pages, adj_vertex);
            page_insert_in_file(page_adj, page);
            string_destroy(adj_vertex);

        }

        fscanf(fp,"%*[ \n\t]");

        string_destroy(vertex);
    }
    
    fclose(fp);

}
Search * search_read(ST * stopwords){
    // o caractere de fim de arquivo seja lido.
    // precisa ler ate o fim de um arquivo na verdade
    Search * se = search_create();
    
    char string[STRING_SZ];
    char c;
    while(scanf("%199s",string) == 1){
        String * word = string_create(string);
        if(!ST_get(stopwords, word)){ // acho que nao precisa fazer, mas por enquanto vou deixar
        // é que sempre que fazer o get na sys->term_list, vai retornar nada
            search_insert_word(se,word);
        }
        else{
            string_destroy(word);
        }
        
        if(scanf("%c", &c) != 1)
            break;
        
        if(c == '\n' || c == '\r')
            break;
    }

    if(search_num_words(se)== 0){
        search_destroy(se);
        return NULL;
    }
    

    return se;
}