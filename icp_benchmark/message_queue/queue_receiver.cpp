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

void execution(int run){
	
	cout << "Running " << run << "..." << '\n';
	
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
		while(true){
			msgrcv(msgqidSR, &msgqmpSR, sizeof(msgqmpSR), 0, MSG_NOERROR);
			//cout << "Receive " << msgqmpSR.buf << '\n';
			char *aux = strtok(msgqmpSR.buf, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				break;
			}
		}
		
		msgqmpRS.type = 1;
		strcpy(msgqmpRS.buf, (to_string(pos)+'$'+words[pos]).c_str());
		msgsnd(msgqidRS, &msgqmpRS, sizeof(msgqmpRS), 0);
		//cout << "Sent " << msgqmpRS.buf << '\n';
		
		pos++;
	}
	
	/**************************/
	
	cout << "... done." << "\n\n";
	 
   	return;
}


int main(int argc, char* argv[]) {
	
	cout << "Starting MESSAGE QUEUE benchmark ...\n\n";
	
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		execution(i);
	}
	
	cout << "... done MESSAGE QUEUE benchmark ...\n\n";
	

	return 0;
}

