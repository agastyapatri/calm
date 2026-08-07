#include <calm.hpp> 
#include <cstdlib>
#include <cpr/cpr.h>
#include <fstream> 
#include <iostream>

namespace calm{
CALM_STATUS load_dotenv(std::string path_to_env){
	std::string variable = "";
	std::fstream file(path_to_env);
	if(!file.is_open())	return CALM_ERR_FILE_NOT_FOUND;
	std::string line; 
	while(std::getline(file, line)){
		if(line.empty() || (line[0] == '#'))	continue;
		size_t delimiter_pos = line.find("=");
		size_t quote_pos = std::min(line.find("\""), line.find("\'"));
		if((delimiter_pos == std::string::npos) || (delimiter_pos > quote_pos))	return CALM_ERR_ENV_FORMAT;
		std::string key = line.substr(0, delimiter_pos);
		std::string value = line.substr(delimiter_pos + 1);
		if(value.size() >= 2 && value.front() == '"' && value.back() == '"'){
			value = value.substr(1, value.size() - 2);

		}
		setenv(key.c_str(), value.c_str(), 1);
	}
	return CALM_OK;
}


Response Model::invoke(std::string content){
	std::string chat_completion_endpoint = _base_url + "chat/completions";

	json payload;
	payload["max_tokens"] = _max_tokens;
	payload["model"] = _model_name; 
	payload["temperature"] = _temperature;
	payload["messages"] = json::array(); 
	json user_msg = {{"role", "user"}, {"content", content}}; 
	payload["messages"].push_back(user_msg);

	cpr::Header req_header{
		{"Content-Type", "application/json"},
		{"Authorization", "Bearer " + _api_key},
	};
	cpr::Body req_body = cpr::Body(payload.dump(4));
	cpr::Response r = cpr::Post(
		cpr::Url(chat_completion_endpoint),
		req_header, 
		req_body
	);
	return Response(r);
}

Response Model::list_models(){
	std::string models_endpoint = _base_url + "models";
	cpr::Response r = cpr::Get(cpr::Url(models_endpoint));
	return Response(r);
}



Response::Response(cpr::Response response){
	_status_code = response.status_code;
	_content 	 = response.text; 
}


























}
