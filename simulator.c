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
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
      #include <sys/stat.h>


void *updateScreen(void *ptr);
void getKeyboardInput(void *arg);
void toggleLight();
void initializePort();
void writeToPort(uint8_t out);
/*
uint8_t readFromPort(void *ptr);
void *simulation(void *arg);*/
FILE *file;

int carsWaitingOnNorth = 0, carsWaitingOnSouth = 0, carsOnBridge = 0;
bool redOnNorth = false, redOnSouth = false;

int main(void)
{
	pthread_t screen, input, status;
    initializePort();
    pthread_create(&screen, NULL, updateScreen, NULL);
	//pthread_create(&input, NULL, getKeyboardInput, NULL);
	//pthread_create(&status,NULL, simulation, NULL);
	getKeyboardInput(NULL);
	return 1;
}

void *updateScreen(void *arg){
	while(1){
		printf("Cars queueing north side: %d \n Cars queueing south side: %d\n Cars on bridge: %d\n",carsWaitingOnNorth, carsWaitingOnSouth, carsOnBridge);
		if(redOnNorth && redOnSouth){
			printf("North light is ");
			printf("\033[0;31m");
			printf("red \n");
			printf("\033[0m");
			
			printf("South light is ");
			printf("\033[0;31m");
			printf("red \n");
			printf("\033[0m");
		} else if (redOnSouth){
			printf("North light is ");
			printf("\033[0;32m");
			printf("green \n");
			printf("\033[0m");

			printf("South light is ");
			printf("\033[0;31m");
			printf("red \n");
			printf("\033[0m");
		} else {
			printf("North light is ");
			printf("\033[0;31m");
			printf("red \n");
			printf("\033[0m");

			printf("South light is ");
			printf("\033[0;32m");
			printf("green \n");
			printf("\033[0m");
		}
		sleep(1);
	}
}

void getKeyboardInput(void *arg){
	while(1){
		char x = getchar();
		switch(x){
			case 'n':
			carsWaitingOnNorth++;
			//writeToPort(NULL);
			break;
			case 's':
			carsWaitingOnSouth++;
			//writeToPort(NULL);
			break;
			case 'e':
			return;
			//writeToPort(NULL);
			break;
			case 't':
			toggleLight();
			break;
			default:
			break;
		}
	}
}

void toggleLight(){
	if(!redOnNorth){
		redOnNorth = true;
		redOnSouth = false;
	} else {
		redOnNorth = false;
		redOnSouth = true;		
	}
}

void initializePort(){
	int COM1 = open("/dev/ttyS0", O_RDWR);
	struct termios port;
	
	tcgetattr(COM1, &port);	
	
	cfsetispeed(&port,B9600);
	cfsetospeed(&port,B9600);
	port.c_cflag = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
	
	tcsetattr(COM1, TCSANOW ,&port);
	close(COM1);
}

void writeToPort(uint8_t out){	
	int COM1 = open("/dev/ttyS0", O_RDWR);
	if(COM1 == 0)	
		printf("Open failed \n");
	
	int confirm = write(COM1, &out, sizeof(out));
	if(confirm == 0)
		printf("Write failed \n");
	close(COM1);
}


/*
void *simulation(void *arg){
	while(1){
		uint8_t x = readFromPort(NULL);
		switch(x){
			case :
			break;
			
		}
	}
}

uint8_t readFromPort(void *ptr){
	file = open("/dev/ttyS0", O_RWDR);
	if(file== NULL)
		printf("Open failed \n");
	int confirm = read(file,data,sizeof(data));
	if(confirm == 0)
		printf("Read failed \n");
	close(file);
	return data;
}


*/
// int read = read(FILE)