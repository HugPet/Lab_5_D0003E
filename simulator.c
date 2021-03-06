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
void *readFromPort(void *ptr);
void *simulation(void *arg);
void sendToBridge();
void *removeFromBridge(void *ptr);


int carsWaitingOnNorth = 0, carsWaitingOnSouth = 0, carsOnBridge = 0;
bool redOnNorth = true, redOnSouth = true;
int COM1 = 0;
int carsOnBridgeOriginal = 0;

int main(void)
{
	pthread_t screen, updateLight, status;
    initializePort();
    pthread_create(&screen, NULL, updateScreen, NULL);
	pthread_create(&updateLight, NULL, readFromPort, NULL);
	pthread_create(&status,NULL, simulation, NULL);
	getKeyboardInput(NULL);
	
	return 1;
}

void *updateScreen(void *arg){
	while(1){
		printf("Cars queueing north side: %d \nCars queueing south side: %d \nCars on bridge: %d\n",carsWaitingOnNorth, carsWaitingOnSouth, carsOnBridge);
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
			writeToPort(0x1);
			break;
			case 's':
			carsWaitingOnSouth++;
			writeToPort(0x4);
			break;
			case 'e':
			return;
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
	COM1 = open("/dev/ttyS0", O_RDWR);
	if (COM1 < 0){
		printf("COM1 failed\n");	
	}
	tcflush(COM1,TCIFLUSH);
	struct termios port;
	
	if (tcgetattr(COM1, &port))
		printf("getAttr failed\n");
	
	cfsetispeed(&port,B9600);
	cfsetospeed(&port,B9600);
	port.c_cflag = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
	port.c_cflag &= ~(ECHO | ECHONL | ICANON);
	
	port.c_cc[VTIME] = 10;
	port.c_cc[VMIN] = 1;
	
	
	if (tcsetattr(COM1, TCSANOW ,&port))
		printf("setAttr failed\n");
}

void writeToPort(uint8_t out){		
	int confirm = write(COM1, &out, sizeof(out));
	if(confirm == 0)
		printf("Write failed \n");
}

void *simulation(void *arg){
	while(1){
		while(!redOnNorth){
			if (carsWaitingOnNorth){
				carsWaitingOnNorth--;
				carsOnBridge++;
				sendToBridge();
				writeToPort(0x2);
				sleep(1);
			}
		}
		
		while(!redOnSouth){
			if(carsWaitingOnSouth){
				carsWaitingOnSouth--;
				carsOnBridge++;
				sendToBridge();
				writeToPort(0x8);
				sleep(1);
			}
		}
		
		/*if(carsOnBridge && !redOnNorth)
			carsOnBridgeOriginal = carsOnBridge;
			while(carsOnBridge){
				if(carsOnBridge==1){
					sleep(5-carsOnBridgeOriginal);
					carsOnBridge--;
				} else {
					sleep(1);
					carsOnBridge--;
				}
			}*/
		
		//if (redOnNorth && redOnSouth){
		//	sleep(1);
		//}
	}
}

void sendToBridge(){
	pthread_t newCar;
	pthread_create(&newCar, NULL, removeFromBridge, NULL);
}


void *removeFromBridge(void *ptr){
	sleep(5);
	carsOnBridge--;
	pthread_exit(NULL);
}


void *readFromPort(void *ptr){
	uint8_t data;
	while(1){
		int confirm = read(COM1,&data,sizeof(data));
		//	data = (data >> 4);
		if (confirm > 0){
			if(data == 0x9){
				redOnNorth = false;
				redOnSouth = true;
			} else if (data == 0x6){
				redOnNorth = true;
				redOnSouth = false;				
			} else if (data == 0xA){
				redOnNorth = true;
				redOnSouth = true;
			}
		//sleep(1);
		}
	}
}