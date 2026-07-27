#ifndef CALM_H
#define CALM_H

//	calm errors and return codes. 
typedef enum {
	CALM_OK = 0, 

	CALM_ERR_ENV_NOT_FOUND, 	//	.env file not found
	CALM_ERR_ENV_VAR_MISSING, 	//	.env file exists, but the variable does not exist
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
calm_status calm_env_get(const char* path, const char* key, char **out_values);








#endif /* ifndef CALM_H */
