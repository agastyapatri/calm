#ifndef CALM_H
#define CALM_H
#include <curl/curl.h> 
#include <cJSON.h> 


//	calm errors and return codes. 
typedef enum {
	CALM_OK = 0, 
	CALM_ERR_ENV_NOT_FOUND, 	//	.env file not found
	CALM_ERR_ENV_VAR_MISSING, 	//	.env file exists, but the variable does not exist
	CALM_ERR_MALFORMED_VAR,		//	.env file contains malformed entries
	CALM_ERR_CURL_INIT, 		//	failure in initialzing curl 
	CALM_ERR_CURL_REQUEST,		//	failure in the curl request itself. 
	CALM_ERR_HTTP_UNAUTHORIZED, //	HTTP 401
	CALM_ERR_HTTP_RATE_LIMIT, 	//	HTTP 429 
	CALM_ERR_HTTP_SERVER, 		//	HTTP 5xx 
	CALM_ERR_HTTP_OTHER, 		//	any other HTTP failure
	CALM_ERR_JSON_PARSE, 		//	error in parsing JSON (includes invalid JSON errors in the body)
	CALM_ERR_JSON_UNEXPECTED, 	//	unexpected shape in valid JSON
	CALM_ERR_ALLOC, 			//	memory related errors.
} calm_status;


static inline const char* _calm_str_err(calm_status status_code){
	if(status_code == CALM_ERR_ENV_NOT_FOUND)	 return "Target environment file not found\n";
	if(status_code == CALM_ERR_ENV_VAR_MISSING)	 return "Target environment variable not found.\n";
	if(status_code == CALM_ERR_MALFORMED_VAR)	 return "Target environment variable is malformed.\n";
	if(status_code == CALM_ERR_CURL_INIT)	     return "Error in initializing cURL.\n";
	if(status_code == CALM_ERR_CURL_REQUEST)	 return "Error in cURL request.\n";
	if(status_code == CALM_ERR_HTTP_UNAUTHORIZED)return "HTTP err. 401; Unauthorized.\n";
	if(status_code == CALM_ERR_HTTP_RATE_LIMIT)	 return "HTTP err. 429; Rate Limited.\n";
	if(status_code == CALM_ERR_HTTP_SERVER)	     return "HTTP err. 5xx; Server Error.\n";
	if(status_code == CALM_ERR_HTTP_OTHER)	     return "Misc. HTTP Error.\n";
	if(status_code == CALM_ERR_JSON_PARSE)	     return "Error in parsing JSON.\n";
	if(status_code == CALM_ERR_JSON_UNEXPECTED)	 return "Unexpected Shape in Valid JSON.\n";
	if(status_code == CALM_ERR_ALLOC)	         return "Memory allocation error; NULL received.\n";
	return NULL;
}



#define CALM_CHECK(status, optional_free)											  \
		if(status != CALM_OK){							                              \
			fprintf(stderr, "Error in calm: %d; %s", status, _calm_str_err(status));\
			if(optional_free != NULL)	free(optional_free);						  \
			return 1;									                              \
		}												                              \




typedef struct calm_client  calm_client;

calm_status calm_client_create(const char* api_key, const char* model, calm_client** out);
void calm_client_destroy(calm_client* client);

typedef struct {
	char* content; 		//	the model's reply text, NULL on failure
	char* error; 		//	human-readable erro message, NULL on success 
	int http_status; 	//	0 if no HTTP response was received.
} calm_response;
void calm_response_destroy(calm_response* response);



calm_status calm_client_chat(calm_client *client, const char* prompt, calm_response *out);


//	Reads a .env style file. Values are stored in out_values
calm_status calm_env_get(const char* path, const char* key, char **out_value);

typedef struct {
	char* data; 
	size_t size; 
} calm_buffer;
calm_status calm_buffer_init(calm_buffer* buf);

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);





#endif /* ifndef CALM_H */
