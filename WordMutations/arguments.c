#include "headers.h"

char* get_arguments(int argc, char **argv, char *file_name, char extension[]){

    char *dict_extension = NULL;
    int dots = 0;
    int argument_size = 0;
    int index = 0;
    int i = 0;
    
    //primeiro que tudo verificar se foram inseridos 2 argumentos
    if(argc != 3){
        exit(0);
    }

    //para selecionar o argumento a analisar
    if(strcmp(extension, "dict") == 0){
        index = 1;
    }else{
        index = 2;
    }
    
    argument_size = strlen(argv[index]);
    
    //agora temos de verificar se o primeiro argumento tem a extensão .dict
    for (int i = 0; i < argument_size; i++){

        if(argv[index][i] == '.'){
            dots ++; 
            dict_extension =  (char*) malloc(sizeof(char) * (argument_size - i + 1));
            int k  = 0;
            for(int j = i + 1; j < argument_size ; j++ , k++ ){
                dict_extension[k] = argv[index][j];
            }
            dict_extension[k] = '\0';
            
            if(strcmp(dict_extension, extension) != 0){
                free(dict_extension);
                exit(0);
            }
            break;
        }
        
    }
    //o ficheiro nem tinha extensao
    if(dots == 0){
        exit(0);
    }

    if(index == 1){
        free(dict_extension);
        return file_name; //no .dict nao precisamos do nome 
    } 

    file_name = (char*) malloc(sizeof(char) * (argument_size - 5 + 1)); //-5 por causa da .dict e +1 por causa do '/0'

    //copiar o file_name
    for(i = 0; i < argument_size - 5; i++){
        file_name[i] = argv[index][i];
    }
    file_name[i] = '\0';

    
    free(dict_extension);
    return file_name; 
}