#include <stdio.h> 
#include <curl/curl.h> 
#include <cJSON.h> 
#include <stdlib.h>
#include <calm.h> 


int main(void){
	char* path_to_env = ".env";
	char* api_key = NULL;
	calm_status status = calm_env_get(path_to_env, "URL", &api_key);
	if(status != CALM_OK){
		fprintf(stderr, "Failed to get API key: %d\n", status);
		return 1;
	}

	// for(int i = 0; i < 10; i++){
	// 	printf("%c", api_key[i]);
	// }

	free(api_key);
	return 0;

}
