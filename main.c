#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0
#define LSH_RL_BUFFSIZE 1024

void lsh_loop(void);
char* lsh_read_line(void);
char** lsh_split_line(char*);
int lsh_execute_line(char**);

int main(int argc, char **argv){

    lsh_loop();

    return EXIT_SUCCESS;
}

void lsh_loop(){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute_line(args);

        free(line);
        free(args);
    }while (status);
}

char* lsh_read_line(void){
    int buffsize = LSH_RL_BUFFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if(!buffer){
        fprintf(stderr, "lsh allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }
        position++;

        if(position >=buffsize){
            buffsize += LSH_RL_BUFFSIZE;
            buffer = realloc(buffer, buffsize);

            if(!buffer){
                fprintf(stderr,"lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

}
