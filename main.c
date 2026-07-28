#include <stdio.h> 
#include <curl/curl.h> 
#include <cJSON.h> 
#include <stdlib.h>
#include <calm.h> 


int main(void){
	char* path_to_env = ".env";
	char* api_key = NULL;
	char* base_url = NULL;
	char* model_name = NULL;
	calm_status status = calm_env_get(path_to_env, "OPENROUTER_API_KEY", &api_key);
	if(status != CALM_OK){
		fprintf(stderr, "Failed to get API key: %d\n", status);
		return 1;
	}
	status = calm_env_get(path_to_env, "URL", &base_url);
	if(status != CALM_OK){
		fprintf(stderr, "Failed to get URL: %d\n", status);
		return 1;
	}
	status = calm_env_get(path_to_env, "NEMOTRON_3_NANO", &model_name);
	if(status != CALM_OK){
		fprintf(stderr, "Failed to get model_name: %d\n", status);
		return 1;
	}

	printf("%s\n", api_key);
	printf("%s\n", base_url);
	printf("%s\n", model_name);

	free(api_key);
	return 0;

}
