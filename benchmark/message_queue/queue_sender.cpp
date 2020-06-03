#include<iostream>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<iomanip> 
#include<string.h>
#include<fstream>
#include<assert.h>

using namespace std;

#define FILESR "QUEUE_SR"
#define FILERS "QUEUE_RS"
#define KEYSR 0x1212
#define KEYRS 0x2121
#define PERMS 0644

#define NUMBER_EXECUTIONS 100
#define MESSAGE_SIZE 10 // should be [10, 1000, 100000]
#define NUMBER_MESSAGES 100000 // should be [100000, 1000, 10]
// use the flag   "-fno-stack-protector"   on compile

string words[NUMBER_MESSAGES];

struct msgqueue {
   long type;
   char buf[MESSAGE_SIZE+10];
};

double execution(int run){
	
	clock_t start, end;
	cout << "Running " << run << "..." << '\n';
	 
	start = clock(); 
	
	/**************************/
	
	key_t keySR;
	int msgqidSR;
	msgqueue msgqmpSR;
	struct msqid_ds msdSR;
	struct ipc_perm msg_permSR;
	msg_permSR.mode = PERMS;
	msdSR.msg_perm = msg_permSR;
	msdSR.msg_qbytes = MESSAGE_SIZE+10+64;
	
	while(true){
		keySR = ftok(FILESR, KEYSR);
		if(keySR!=-1) break;
	}
	
	while(true){
		msgqidSR = msgget(keySR, IPC_CREAT);
		if(msgqidSR!=-1) break;
	}
	msgctl(msgqidSR, IPC_SET, &msdSR);
	
	key_t keyRS;
	int msgqidRS;
	msgqueue msgqmpRS;
	struct msqid_ds msdRS;
	struct ipc_perm msg_permRS;
	msg_permRS.mode = PERMS;
	msdRS.msg_perm = msg_permRS;
	msdRS.msg_qbytes = MESSAGE_SIZE+10+64;
	
	while(true){
		keyRS = ftok(FILERS, KEYRS);
		if(keyRS!=-1) break;
	}
	
	while(true){
		msgqidRS = msgget(keyRS, IPC_CREAT);
		if(msgqidRS!=-1) break;
	}
	msgctl(msgqidRS, IPC_SET, &msdRS);
	
		
	int pos = 0;
	while(pos < NUMBER_MESSAGES){
		msgqmpSR.type = 1;
		strcpy(msgqmpSR.buf, (to_string(pos)+'$'+words[pos]).c_str());
		msgsnd(msgqidSR, &msgqmpSR, sizeof(msgqmpSR), IPC_NOWAIT);
		//cout << "Sent " << msgqmpSR.buf << '\n';
		
		while(true){
			msgrcv(msgqidRS, &msgqmpRS, sizeof(msgqmpRS), 0, MSG_NOERROR);
			//cout << "Receive " << msgqmpRS.buf << '\n';
			char *aux = strtok(msgqmpRS.buf, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				break;
			}
		}	
		
		pos++;
	}
	
	
	/**************************/
	
	end = clock();
	
	cout << "... done." << '\n';
	 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
   	cout << "Time taken by MESSAGE QUEUE in execution " << run << " is : " << fixed << time_taken << setprecision(8) << " sec\n\n"; 
   	
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
	
	system("rm " FILESR);
	system("rm " FILERS);
	
	cout << "Getting correct words ...";
	saveWords(argv[1]);
	cout << "... done\n\n";
	
	system("touch " FILESR);
	system("touch " FILERS);
	
	cout << "Start the cliente ...\n\n";
	sleep(3);
	
	cout << "Starting MESSAGE QUEUE benchmark ...\n\n";
	
	
	double totalTime = 0.0;
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		totalTime += execution(i);
	}
	
	cout << "... done MESSAGE QUEUE benchmark ...\n\n";
	cout << "Total time: " << fixed << totalTime << setprecision(8) << " sec\n";
	cout << "Average time: " << fixed << totalTime/NUMBER_EXECUTIONS << setprecision(8) << " sec\n";
	
	system("rm " FILESR);
	system("rm " FILERS);

	return 0;
}

