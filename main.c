#include <stdio.h> 
#include <curl/curl.h> 
#include <cJSON.h> 
#include <stdlib.h>


int main(void){
	char* openrouter_api_key = getenv("OPENROUTER_API_KEY");
	if(!openrouter_api_key){
		fprintf(stderr, "api key could not be read");
	}
	printf("OpenRouter API Key: %s\n", openrouter_api_key);
	return 0;
}
