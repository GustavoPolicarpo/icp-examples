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

	key_t key;
	int msgqid;
	msgqueue msgqmp;
	
	key = ftok(FILE, QUEUE_KEY);
	if(key == -1) error("Unable to get key");
	
	msgqid = msgget(key, PERMS);
	if(msgqid == -1) error("Unable to get message queue");
	
	for(;;){
		msgrcv(msgqid, &msgqmp, sizeof(msgqmp), 2, 0);
		printf("Received string: \"%s\" and string length is %d and your type is %d\n", msgqmp.buf, (int)strlen(msgqmp.buf), (int)msgqmp.type);
		if(strcmp(msgqmp.buf, "end")==0) break;
	}
	
	system("rm " FILE);
   
   return 0;
}
