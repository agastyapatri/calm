#include "calm.h"
#include <curl/curl.h> 
#include <stdlib.h>
#include <string.h>
struct calm_client{
	CURL* curl;
	char* api_key;
	char* model;
};

calm_status calm_env_get(const char* path, const char* key, char **out_value){
	FILE* file = fopen(path, "r");
	if(!file){
		*out_value = NULL;
		return CALM_ERR_ENV_NOT_FOUND;
	} 
	char line[512];
	while(fgets(line, sizeof(line), file)){
		line[strcspn(line, "\n")] = 0;
		if(line[0] == '\0' || line[0] == '#')	continue;
		char* delimiter = strchr(line, '=');
		if(!delimiter){
			*out_value = NULL;
			fclose(file);
			return CALM_ERR_MALFORMED_VAR;
		} 
		*delimiter = '\0';
		char* _key = line; 
		char* _value = delimiter + 1;
		if(!strcmp(_key, key)){
			size_t var_len = strlen(_value);
			if(!var_len){
				*out_value = NULL;
				fclose(file);
				return CALM_ERR_MALFORMED_VAR;
			}
			if((_value[0] == '\"') || (_value[0] == '\'')){
				_value += 1;
				var_len = strlen(_value);
			}	
			if((var_len > 0) && ((_value[var_len - 1] == '\"') || (_value[var_len - 1] == '\''))){
				_value[var_len - 1] = '\0';
			}
			*out_value = (char*)malloc((strlen(_value) + 1)*sizeof(char));
			if(!out_value){
				fclose(file);
				return CALM_ERR_ALLOC;
			}
			strcpy(*out_value, _value);
			fclose(file);
			return CALM_OK;
		}
	}
	fclose(file);
	*out_value = NULL;
	return CALM_ERR_ENV_VAR_MISSING;
}
