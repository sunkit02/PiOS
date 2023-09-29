#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../string.h"

#include ".h"


bool canFindStringLength();
bool canCatStrings();
bool canCopyMemory();
bool canCatMemory();
bool canSetMemory();
bool canCompareStrings();

int main(void){

	canFindStringLength();
	canCatStrings();
	canCopyMemory();
	canCatMemory();
	canSetMemory();
	canCompareStrings();

}

bool canFindStringLength() {
	size_t expectedValue = 10;
	char testStr[expectedValue];
	if (strlen(testStr) == expectedValue){
		printf("Passed - Can Find String Length");
		return true;
	}else{
		printf("FAILED - Can Find String Length");
		return false;
	}
}

bool canCatStrings(){
	char str1 = 'Hello ';
	char str2 = 'world';
	char expectedValue = 'Hello world';
	
	if (strcmp(strcat(str1, str2), expectedValue)){
		printf("Passed - Can Cat Strings");
		return true;
	}else{
		printf("FAILED - Can Cat Strings");
		return false;
	};
}

bool canCopyMemory(){
	char memSource[10] = 'Hello ';
	char memDestination[10];
	memcpy(memDestination, memSource, 10);

	if (strcmp(memSource, memDestination)){
		printf("Passed - Can Copy Memory");
		return true;
	}else{
		printf("FAILED - Can Copy Memory");
		return false;
	};
}

bool canCatMemory(){
	char memSource1[7] = 'Hello ';
	char memSource2[6] = 'world';
	char memDestination[13];
	char expectedValue = 'Hello world';
	memcat(memDestination, memSource1, memSource2, 7, 6);

	if (strcmp(expectedValue, memDestination)){
		printf("Passed - Can Copy Memory");
		return true;
	}else{
		printf("FAILED - Can Copy Memory");
		return false;
	};
};

bool canSetMemory(){
	char message[15] = 'Hello World';
	char expectedValue[15] = '$$$lo World';
	memset(message, '$', 3);
	
	if (strcmp(expectedValue, message)){
		printf("Passed - Can Set Memory");
		return true;
	}else{
		printf("FAILED - Can Set Memory");
		return false;
	}
};

bool canCompareStrings(){
	char str1 = "hello";
	char str2 = "hello";
	char str3 = "world";

	if(strcmp(str1, str2) && strcmp(str2,str3) == 1){
		printf("Passed - Can Compare Strings");
		return true;
	}else{
		printf("FAILED - Can Compare Strings");
		return false;
	};
};
