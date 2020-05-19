#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILE "MY_NAMED_PIPE"
#define BUF_SIZE 100

void error(std::string message){
	std::cout << message << '\n';
	exit(1);
}

int main() {

	int fd;
	char message[BUF_SIZE];
	
	fd = open(FILE, O_CREAT|O_WRONLY);
	if(fd == -1) error("Unable to open file for writing");
	
	for(;;){
		std::cout << "Write the message: (\"end\" to finish) "; std::cin >> message;
		printf("Sent string: \"%s\" and string length is %d\n", message, (int)strlen(message));
		write(fd, message, strlen(message));
		if(strcmp(message, "end")==0) break;
	}
	
	close(fd);
	
	return 0;
}
