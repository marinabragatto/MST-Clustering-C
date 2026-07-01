#include "ioReader.h"
#include "page.h"


void read_page_terms(Page* page, char * dir, ST * stop_words, ST * term_list, char * exist);

ST * read_stop_words(char * dir, char * exist){
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

    while(fscanf(fp,"%199s", string) != EOF){
        
        // String * str_ptr = string_create(string);
        // char * c ;
        // string_print(str_ptr); remover
        int sucess = ST_PUT(stop_words, string, exist);
        // if (!sucess)
        //     string_destroy(str_ptr);
        i++;
    }


    fclose(fp);

    return stop_words;
}



StringMapVector * read_pages_name(char * dir){
    
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

    while(fscanf(fp,"%199s", string) != EOF){
        String * page_name = string_create(string);

        Page * page = page_create(page_name);
        // printf("PAGE NAME : %d: ", i); remover
        // string_print(page_name); remover
        SMV_insert(smv, page, page_name);
        i++;
    }

    fclose(fp);

    return smv;


}

ST * read_terms(char * dir,  StringMapVector * pages, ST * stop_words, char * exist){
    ST * term_list = ST_init();

    int i = 0;

    //printf("Leitura do conteudo das paginas\n"); //debug
    for(int i = 0; i < SMV_get_size(pages); i ++){
        //printf("Page %d: ", i);
        Page * page = SMV_get_by_idx(pages, i);
        //string_print_v2(page_get_name(page));
        //printf("\n");
        
        read_page_terms(page, dir, stop_words, term_list, exist);
        //printf("\n\n");
    }

    
    return term_list;
}


void read_page_terms(Page * page, char * dir, ST * stop_words, ST * term_list, char * exist){

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
        // String * term = string_create(string); 
        string_tolower(string);

        Vector * vet_term_docs = NULL;

        if(!ST_get(stop_words, string)){ // nao eh uma stop word
            if(vet_term_docs = ST_get(term_list, string)){
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
                ST_PUT(term_list, string, vet_term_docs);
            }
            // String * term = string_create(string); 
            page_insert_word(page, string,exist);// talvez p reduzir memoria reaproveitar o ponteiro
        }
        else{
            // eh uma stopword
            //printf("era stop word:");
            //string_print(term);
            // string_destroy(term);
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
    while(fscanf(fp,"%199s", string) != EOF){
        // String * vertex = string_create(string); // nome do arquivo (vertice)
        // string_print(vertex); // remover
        int n; // numero de elementos associados
        fscanf(fp,"%d", &n);
        // printf(" out : %d \n", n);  // remover
        
        Page * page = SMV_get_by_key(pages, string); 
        page_set_out_number(page, n);


        for(int i = 0 ; i < n; i++){
            fscanf(fp,"%199s", string);
            
            // String * adj_vertex = string_create(string); // nome do arquivo adjacentes ao vertex 
            // printf("\t"); // remover
            // string_print(adj_vertex); // remover
            Page * page_adj = SMV_get_by_key(pages, string);
            page_insert_in_file(page_adj, page);
            // string_destroy(adj_vertex);

        }


        // string_destroy(vertex);
    }
    
    fclose(fp);

}
Search * search_read_print(ST * stopwords){
    // o caractere de fim de arquivo seja lido.
    // precisa ler ate o fim de um arquivo na verdade
    Search * se = search_create();
    char string[STRING_SZ];
    char c;
    int iteration = 0;
    while(scanf("%199s",string) == 1){
        if(iteration == 0){
            printf("search:");
            iteration++;
        }
        
        printf(" ");
        string_print_v2(string);
        if(!ST_get(stopwords, string)){ // acho que nao precisa fazer, mas por enquanto vou deixar
            String * word = string_create(string); // faz o malloc so se precsa
            // é que sempre que fazer o get na sys->term_list, vai retornar nada
            search_insert_word(se,word);
        }
        
        if(scanf("%c", &c) != 1)
            break;
        
        if(c == '\n' || c == '\r')
            break;
    }

    if(iteration==0){
        search_destroy(se);
        return NULL;
    }
    printf("\n");
    
    return se;
}