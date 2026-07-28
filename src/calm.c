#include "calm.h"
#include <curl/curl.h> 
#include <stdlib.h>
#include <string.h>
struct calm_client{
	CURL* curl;
	char* api_key;
	char* model;
};

//	TODO: finish this.
calm_status calm_env_get(const char* path, const char* key, char **out_value){
	FILE* file = fopen(path, "r");
	if(!file)	return CALM_ERR_ENV_NOT_FOUND;
	char line[512];
	while(fgets(line, sizeof(line), file)){
		line[strcspn(line, "\n")] = 0;
		if(line[0] == '\0' || line[0] == '#')	continue;
		char* _key = strtok(line, "=");
		printf("%s\n", _key);



	}
	fclose(file);
	return CALM_ERR_ENV_VAR_MISSING;
}
