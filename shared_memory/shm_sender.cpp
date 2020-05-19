#include <iostream>
#include<sys/shm.h>
#include<string.h>

#define BUF_SIZE 100
#define SHM_KEY 0x1234

void error(std::string message){
	std::cout << message << '\n';
	exit(1);
}

struct shmseg {
   int numberMessages;
   char buf[BUF_SIZE];
};

int main(int argc, char *argv[]) {
	int shmid;
	shmseg *shmp;
	
	shmid = shmget(SHM_KEY, sizeof(shmseg), 0644|IPC_CREAT);
	if(shmid == -1) error("Unable to create shared memory");
	
	shmp = (shmseg*) shmat(shmid, NULL, 0);
	if(shmp == (void *) -1) error("Unable to attach segment");
	
	for(;;){
		std::cout << "Write the message: (\"end\" to finish) "; std::cin >> shmp->buf;
		printf("Written string: \"%s\" and string length is %d\n", shmp->buf, (int)strlen(shmp->buf));
		shmp->numberMessages++;
		if(strcmp(shmp->buf, "end")==0) break;
	}
	
	int status;
	status = shmdt(shmp);
	if(status == -1) error("Unable to detach segment");
	
	status = shmctl(shmid, IPC_RMID, 0);
	if(status == -1) error("Unable to free memory");
	
	return 0;
}
