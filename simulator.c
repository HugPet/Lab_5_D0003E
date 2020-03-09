/*
 * Simulator.c
 *
 * Created: 2020-03-09 11:32:16
 * Author : josvil-8
 */ 

#include <pthread.h>
#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <semaphore.h>


void *writeToPort(void *ptr);
void *writeToConsole(void *ptr);
void *getKeyboardInput(void *arg);
char *readFromPort(void *ptr);
void *createCar(void *arg);
FILE *file;


int main(void)
{
	pthread_t test1, test2;
	char *message = "kebab";
    /* Replace with your application code */
    pthread_create(&test1, NULL, writeToConsole, (void*)message);
	pthread_create(&test2, NULL, getKeyboardInput, NULL);
	pthread_join(test1,NULL);
	pthread_join(test2,NULL);
}

void *writeToConsole(void *ptr){
	char *message;
	message = (char*)ptr;
	printf("%s \n", message);
}

void *getKeyboardInput(void *arg){
	while(1){
		char x = getchar();
		switch(x){
			case 'n':
			printf("N \n");
			break;
			case 's':
			printf("S \n");
			break;
			case 'e':
			printf("E \n");
			break;
			default:
			break;
		}
	}
}

void *createCar(void *arg){
	
}

char *readFromPort(void *ptr){
	file = fopen("./test.txt", "r");
	if(file== NULL)
		printf("Open failed \n");
	char data = fread(file,sizeof(char),1)
	fclose(file);
	return data;
}

void *writeToPort(void *ptr){	
	char *message;
	message = (char*)ptr;
	char output[20] = "12345678901234kebab";

	file = fopen("./test.txt", "w");
	if(file== NULL)
		printf("Open failed \n");
	
	int confirm = fwrite(output,sizeof(char),sizeof(output),file);
	if(confirm == 0)
		printf("Write failed \n");
	fclose(file);
}

// int read = read(FILE)