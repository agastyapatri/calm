#ifndef CALM_SRC_CALM_HPP
#define CALM_SRC_CALM_HPP 
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <unordered_map>
#include <vector>

namespace calm{
using json = nlohmann::json;



//	calm error codes for all sorts of errors
typedef enum {
	CALM_OK,
	CALM_ERR_FILE_NOT_FOUND,
	CALM_ERR_VAR_NOT_FOUND,
	CALM_ERR_ENV_FORMAT, 

} CALM_STATUS;


//	reading var_name from path_to_env
CALM_STATUS load_dotenv(std::string path_to_env);

//	TODO
class Model;
class Response;



//	base(?) class for chat models
class Model{
private: 
	std::string _api_key; 
	std::string _model_name; 
	std::string _base_url;
	float _temperature;
	int _max_tokens;
public:
	Model() = default;
	Model(std::string api_key, std::string model_name, std::string base_url, float temperature = 0.0, int max_tokens = 1024): 
		_api_key(api_key), _model_name(model_name),_base_url(base_url), _temperature(temperature), _max_tokens(max_tokens){};
	void set_api_key    (std::string key) {_api_key = key;}
	void set_model_name (std::string name){_model_name = name;}
	void set_base_url   (std::string url) {_base_url = url;}
	void set_temperature(float temp) 	  {_temperature = temp;}
	void set_max_tokens (int tokens) 	  {_max_tokens = tokens;}

	const std::string model_name() const {return _model_name;}
	const std::string base_url  () const {return _base_url  ;}
	float temperature() const {return _temperature;}
	int   max_tokens()  const {return _max_tokens ;}

	Response invoke(std::string content);

	// TODO
	Response invoke(std::unordered_map<std::string, std::string> messages);
	// TODO
	Response list_models();

};


//	Base(?) class for chat model responses 
class Response{
private: 
	int _status_code;
	std::string _text;		//	extracts only the string text from the payload 
	std::string _content;	//	contains the raw HTTP response
	void _read_response();
public:
	Response() = default;
	Response(cpr::Response response);
	int status_code()     const {return _status_code;}
	std::string content() const {return _content;}
	std::string text()    const {return _text;}






};



}


#endif // !CALM_SRC_CALM_HPP
