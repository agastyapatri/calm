#include <curl/curl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <calm.h> 
#define PATH_TO_ENV ".env"




int main(void){
	char* api_key = NULL;
	char* base_url = NULL;
	char* model_name = NULL;
	calm_status status = calm_env_get(PATH_TO_ENV, "OPENROUTER_API_KEY", &api_key);
	status = CALM_ERR_MALFORMED_VAR;
	CALM_CHECK(status);
	free(api_key);





	return 0;
}
