#include<iostream>
#include<string.h>

#define NUMBER_MESSAGES 10
#define MESSAGE_SIZE 100000

int main(void){
	
	for(int i=0; i<NUMBER_MESSAGES; i++){
		int sz = random()%MESSAGE_SIZE+1;
		char message[sz+1];
		for(int j=0; j<sz; j++){
			message[j] = rand()%26+'a';
		}	message[sz] = '\0';
		std::cout << message << '\n';
	}
   
	return 0;
}
