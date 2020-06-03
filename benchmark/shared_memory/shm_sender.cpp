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

double execution(int run){
	
	clock_t start, end;
	cout << "Running " << run << "..." << '\n';
	 
	start = clock(); 
	
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
		while(words[pos].size()<MESSAGE_SIZE) words[pos].push_back('x');
		strcpy(shmpSR->buf, (to_string(pos)+'$'+words[pos]).c_str());
		//cout << "Sent " << shmpSR->buf << '\n';
		
		while(true){
			char message[MESSAGE_SIZE+10];
			strcpy(message, shmpRS->buf);
			//cout << "Receive " << message << '\n';
			char *aux = strtok(message, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				break;
			}
		}	
		
		pos++;
	}
	
	if(run==NUMBER_EXECUTIONS){
		int status;
		status = -1;
		while(status == -1) status = shmdt(shmpSR);
		
		status = -1;
		while(status == -1) status = shmctl(shmidSR, IPC_RMID, 0);
		
		status = -1;
		while(status == -1) status = shmdt(shmpRS);
		
		status = -1;
		while(status == -1) status = shmctl(shmidRS, IPC_RMID, 0);
	}
	
	
	/**************************/
	
	end = clock();
	
	cout << "... done." << '\n';
	 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
   	cout << "Time taken by SHARED MEMORY in execution " << run << " is : " << fixed << time_taken << setprecision(8) << " sec\n\n"; 
   	
   	return time_taken;
}

void saveWords(char path[]){
	ifstream input(path);
	int i = 0;
	while(i<NUMBER_MESSAGES){
		getline(input, words[i]);
		i++;
	}
	return;
}

int main(int argc, char* argv[]) {
	
	
	cout << "Getting correct words ...";
	saveWords(argv[1]);
	cout << "... done\n\n";
	
	cout << "Start the cliente ...\n\n";
	sleep(3);
	
	cout << "Starting SHARED MEMORY benchmark ...\n\n";
	
	
	double totalTime = 0.0;
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		totalTime += execution(i);
	}
	
	cout << "... done SHARED MEMORY benchmark ...\n\n";
	cout << "Total time: " << fixed << totalTime << setprecision(8) << " sec\n";
	cout << "Average time: " << fixed << totalTime/NUMBER_EXECUTIONS << setprecision(8) << " sec\n";
	

	return 0;
}

