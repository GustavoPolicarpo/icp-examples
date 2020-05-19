#include<unistd.h>
#include<iostream>
#include<string.h>

void error(std::string message){
	std::cout << message << '\n';
	exit(1);
}

int main() {

	int pipefds[2];
	int status;
	
	status = pipe(pipefds);
	
	if ( status == -1 ) error("Unable to create pipe\n");
	
	std::string message;
	for(;;){
		std::cout << "Write the message: (\"end\" to finish) "; std::cin >> message;
		
		char writtenMessage[message.size()+1], readMessage[message.size()+1];
		strcpy(writtenMessage, message.c_str()); 
		
		write(pipefds[1], writtenMessage, sizeof(writtenMessage));
		read(pipefds[0], readMessage, sizeof(readMessage));
		
		printf("Written message = %s and Read message = %s\n", writtenMessage, readMessage);
		
		if(strcmp(message, "end")==0) break;
	}
	
	close(pipefds[0]);
	close(pipefds[1]);
	
   
   return 0;
}
