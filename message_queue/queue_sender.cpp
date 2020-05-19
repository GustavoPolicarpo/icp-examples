#include<iostream>
#include<sys/msg.h>
#include<string.h>

#define PERMS 0644

#define FILE "MY_QUEUE_FILE"
#define QUEUE_KEY 0x1234
#define BUF_SIZE 100

void error(std::string message){
	std::cout << message << '\n';
	exit(1);
}

struct msgqueue {
   long type;
   char buf[BUF_SIZE];
};

int main(void) {

	system("touch " FILE);
	
	key_t key;
	int msgqid;
	msgqueue msgqmp;
	
	key = ftok(FILE, QUEUE_KEY);
	if(key == -1) error("Unable to get key");
	
	msgqid = msgget(key, PERMS | IPC_CREAT);
	if(msgqid == -1) error("Unable to get message queue");

	for(;;){
		std::cout << "Write the message: (\"end\" to finish) "; std::cin >> msgqmp.buf;
		
		if(strcmp(msgqmp.buf, "end")==0){
			msgqmp.type = 1;
			msgsnd(msgqid, &msgqmp, sizeof(msgqmp), 0);
			
			msgqmp.type = 2;
			msgsnd(msgqid, &msgqmp, sizeof(msgqmp), 0);
			break;
		}
		
		std::cout << "Write the type: (must be an integer [1 or 2]) "; std::cin >> msgqmp.type;
		
		printf("Sent string: \"%s\" and string length is %d and your type is %d\n", msgqmp.buf, (int)strlen(msgqmp.buf), (int)msgqmp.type);
		msgsnd(msgqid, &msgqmp, sizeof(msgqmp), 0);
	}
	
	int status;
	status = (msgctl(msgqid, IPC_RMID, NULL) == -1);
	if(status == -1) error("Unable to free message queue");
	
   
   return 0;
}
