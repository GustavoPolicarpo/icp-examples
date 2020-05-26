#include <iostream>
#include <sys/stat.h>
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
	
	mknod(FILE, S_IFIFO|0640, 0);
	
	int fd;
	int read_bytes;
	char read_buf[BUF_SIZE];
	
	for(;;){
		fd = open(FILE, O_RDONLY);
		if(fd == -1) error("Unable to open file for reading");
		
		read_bytes = read(fd, read_buf, sizeof(read_buf));
		read_buf[read_bytes] = '\0';

		printf("Received string: \"%s\" and length is %d\n", read_buf, (int)strlen(read_buf));
		
		if(strcmp(read_buf, "end")==0) break;
	}
	
	system("rm " FILE);

	return 0;
}
