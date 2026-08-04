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


std::string invoke(std::string content){
	std::string output = "";
	return output;
}







}
