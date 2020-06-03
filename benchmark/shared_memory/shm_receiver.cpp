#include<iostream>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>
#include<iomanip> 
#include<string.h>
#include<fstream>
#include<assert.h>

using namespace std;

#define KEYSR 0x1234
#define KEYRS 0x4321
#define PERMS 0644

#define NUMBER_EXECUTIONS 100
#define MESSAGE_SIZE 1000 // should be [10, 1000, 100000]
#define NUMBER_MESSAGES 1000 // should be [100000, 1000, 10]

string words[NUMBER_MESSAGES];

struct shmseg {
   char buf[MESSAGE_SIZE+10];
};

void execution(int run){
	
	cout << "Running " << run << "..." << '\n';
	
	/**************************/
	
	int shmidSR;
	shmseg *shmpSR;
	
	while(true){
		shmidSR = shmget(KEYSR, sizeof(shmseg), PERMS|IPC_CREAT);
		if(shmidSR!=-1) break;
	}
	
	while(true){
		shmpSR = (shmseg*) shmat(shmidSR, NULL, 0);
		if(shmpSR != (void *) -1) break;
	}
	
	
	int shmidRS;
	shmseg *shmpRS;
	
	while(true){
		shmidRS = shmget(KEYRS, sizeof(shmseg), PERMS|IPC_CREAT);
		if(shmidRS!=-1) break;
	}
	
	while(true){
		shmpRS = (shmseg*) shmat(shmidRS, NULL, 0);
		if(shmpRS != (void *) -1) break;
	}
	
	int pos = 0;
	while(pos < NUMBER_MESSAGES){
		while(true){
			char message[MESSAGE_SIZE+10];
			strcpy(message, shmpSR->buf);
			//cout << "Receive " << message << '\n';
			char *aux = strtok(message, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				break;
			}
		}	
		
		strcpy(shmpRS->buf, (to_string(pos)+'$').c_str());
		//cout << "Sent " << shmpRS->buf << '\n';
		
		pos++;
	}
	
	/**************************/
	
	cout << "... done." << "\n\n";
	 
   	return;
}


int main(int argc, char* argv[]) {
	
	cout << "Starting SHARED MEMORY benchmark ...\n\n";
	
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		execution(i);
	}
	
	cout << "... done SHARED MEMORY benchmark ...\n\n";
	

	return 0;
}

