#include<iostream>
#include<string.h>

#define NUMBER_MESSAGES 100000
#define MESSAGE_SIZE 10

int main(void){
	
	for(int i=0; i<NUMBER_MESSAGES; i++){
		char message[MESSAGE_SIZE+1];
		for(int j=0; j<MESSAGE_SIZE; j++){
			message[j] = rand()%26+'a';
		}	message[MESSAGE_SIZE] = '\0';
		std::cout << message << '\n';
	}
   
	return 0;
}
