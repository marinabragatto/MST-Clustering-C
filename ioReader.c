/**
 * @file ioReader.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Implementação de funções para a leitura dos arquivos de entrada.
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "ioReader.h"
#include "page.h"


void read_page_terms(Page* page, char * dir, ST * stop_words, ST * term_list, char * exist);

ST * read_stop_words(char * dir, char * exist){
    ST * stop_words = ST_init();
    
    char * dir_name =  define_directory_path(dir, "/stopwords.txt");
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(dir_name);

    char string[STRING_SZ];
    int i = 0;

    while(fscanf(fp,"%199s", string) != EOF){
        int sucess = ST_PUT(stop_words, string, exist);
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
        SMV_insert(smv, page, page_name);
        i++;
    }

    fclose(fp);

    return smv;


}

ST * read_terms(char * dir,  StringMapVector * pages, ST * stop_words, char * exist){
    ST * term_list = ST_init();

    int i = 0;

    int size = SMV_get_size(pages);
    for(int i = 0; i < size; i ++){
        Page * page = SMV_get_by_idx(pages, i);   
        read_page_terms(page, dir, stop_words, term_list, exist);
    }

    
    return term_list;
}


void read_page_terms(Page * page, char * dir, ST * stop_words, ST * term_list, char * exist){

    
    String * page_name = page_get_name(page);
    char * tmp =  define_directory_path(dir, "/pages/");
    char * file_path = define_directory_path(tmp, string_get_char_pointer(page_name,0));
    free(tmp);

    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
     
    char c;
    char string[STRING_SZ];
    while(fscanf(fp,"%199s%c", string, &c) != EOF){
        string_tolower(string);

        Vector * vet_term_docs = NULL;

        if(!ST_get(stop_words, string)){ /*Verifica se o termo e stopword*/
            if(vet_term_docs = ST_get(term_list, string)){ /*Verifica se ja existe vetor associado ao termo atual*/
                Page * last_page = vector_get_last(vet_term_docs);

                String * last_page_name = page_get_name(last_page);
                if(last_page_name != NULL){
                    if(compare(page_name,last_page_name) != 0){ /*Verifica se esse documento ja nao foi inserido como associado ao termo atual*/
                        vector_insert(vet_term_docs, page); /*Se nao foi inserido ainda, insere*/
                    }
                }
            }
            else {
                /*Nao tem ainda um vetor de documentos associados ao termo*/
                vet_term_docs = vector_create(VECTOR_SZ, NULL);
                vector_insert(vet_term_docs, page); /*Insere o documento como associado ao termo*/
                ST_PUT(term_list, string, vet_term_docs);
            }
            page_insert_word(page, string,exist); /*registra o termo na sua pagina (documento)*/
        }
    }
    
    fclose(fp);

}

void read_pages_graph(char * dir, StringMapVector * pages){
    
    char * file_path =  define_directory_path(dir, "/graph.txt");

    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
    
    char string[STRING_SZ]; 

    
    while(fscanf(fp,"%199s", string) != EOF){
        int n; /* Numero de elementos associados */
        fscanf(fp,"%d", &n);
        
        Page * page = SMV_get_by_key(pages, string); 
        page_set_out_number(page, n);

        for(int i = 0 ; i < n; i++){
            fscanf(fp,"%199s", string);            
            Page * page_adj = SMV_get_by_key(pages, string);
            page_insert_in_page(page_adj, page);
        }
    }
    
    fclose(fp);

}
Search * search_read_print(ST * stopwords){
    Search * se = search_create();
    
    char string[STRING_SZ];
    char c;
    int iteration = 0;

    while(scanf("%199s",string) == 1){
        if(iteration == 0){
            printf("search:");
            iteration++;
        }
        
        else{
            printf(" ");
        }
        string_print_v2(string);

        if(!ST_get(stopwords, string)){ 
            String * word = string_create(string); 
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