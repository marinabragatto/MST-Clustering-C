#include "ioreader.h"
#include "page.h"


void read_page_terms(Page* page, char * dir, Vector * stop_words, ST * term_list);

Vector * read_stop_words(char * dir){
    // nossa stopword vai ser uma Simbol Table (hash)
    Vector * stop_words = vector_create(VECTOR_SZ, string_destroy);
    
    char * dir_name =  define_directory_path(dir, "/stopwords.txt");
    print_char(dir_name);
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(dir_name);

    char string[STRING_SZ];
    int i = 0;

    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        String * str_ptr = string_create(string);
        vector_insert(stop_words, str_ptr);
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
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        String * page_name = string_create(string);

        Page * page = page_create(page_name);
        printf("PAGE NAME : ");
        string_print(page_name);
        SMV_insert(smv, page, page_name);
        i++;
    }

    fclose(fp);

    return smv;


}

ST * read_terms(char * dir,  StringMapVector * pages, Vector * stop_words){
    ST * term_list = ST_init();

    int i = 0;

    for(int i = 0; i < SMV_get_size(pages); i ++){
        Page * page = SMV_get_by_idx(pages, i);
        read_page_terms(page, dir, stop_words, term_list);
    }

    
    return term_list;
}


void read_page_terms(Page * page, char * dir, Vector * stop_words, ST * term_list){

    // !!!!!!!!!!!! Essa função já tá lendo os termos de todos os arquivos, falta agora
    // fazer com que ela coloque eles na ST seguindo as condições
    
    // termo -> Vector com documentos que contém ele
    // termo -> Vector de documentos que contém ele
    String * page_name = page_get_name(page);
    char * tmp =  define_directory_path(dir, "/pages/");
    char * file_path = define_directory_path(tmp, string_get_char_pointer(page_name,0));
    free(tmp);

    print_char(file_path);
    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
    

    char string[STRING_SZ];
    while(fscanf(fp,"%[^\n\t ]", string) != EOF){
        fscanf(fp,"%*[\n\t ]");
        // printf("(%s)\n", string);
        String * term = string_create(string); 
        string_tolower(term);
        // string_print(term);

        Vector * vet_term_docs = NULL;

        // ***** tem que verificar se o termo é uma stop word *****
        if(1){ // esse if é para verificar se é uma stop word
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
        }
        string_destroy(term);
    }
    
    fclose(fp);

}

void read_pages_graph(char * dir, StringMapVector * pages){
    
    printf("\n\n\nPAGE LINKS:\n\n\n");

    char * file_path =  define_directory_path(dir, "/graph.txt");

    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
    
    char string[STRING_SZ]; 
    
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
            // printf("\tadj list : (%s)\n", string);
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