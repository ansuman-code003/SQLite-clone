#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
}IOBuffer;

// Function Declaration
IOBuffer* new_IO_buffer();
void printPrompt();
void read_input(IOBuffer*);
void closeIObuffer(IOBuffer*);

//main function
int main(int argc, char* argv[]){
  IOBuffer* ioBuffer = new_IO_buffer();
  //REPL Loop
  while(true){
    printPrompt();
    read_input(ioBuffer);

    if(strcmp(ioBuffer->buffer,".exit") == 0){
      closeIObuffer(ioBuffer);
      exit(EXIT_SUCCESS);
    }else{
      printf("Unrecognized command: '%s'",ioBuffer->buffer);
    }
  }
  return 0;
}


IOBuffer* new_IO_buffer(){
  IOBuffer* iBuffer = (IOBuffer*)malloc(sizeof(IOBuffer));
  iBuffer->buffer = NULL;
  iBuffer->buffer_length = 0;
  iBuffer->input_length=0;
  return iBuffer;
}

void printPrompt() {printf("db > ");}

void read_input(IOBuffer* input_buffer){
  ssize_t bytes_read=getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if(bytes_read <=0){
    printf("Error in input.\n");
    exit(EXIT_FAILURE);
  }
  input_buffer->input_length=bytes_read-1;
  input_buffer->buffer[bytes_read-1]=0;
}

void closeIObuffer(IOBuffer* input_buffer){
  free(input_buffer->buffer);
  free(input_buffer);
}

