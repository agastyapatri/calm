#include <cstdlib>
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <calm.hpp> 
#include <string> 
#include <cpr/cpr.h>

constexpr float TEMPERATURE = 0.0;
constexpr int MAX_TOKENS = 100;

int main(){
	bool status = calm::load_dotenv(".env");
	if(status != calm::CALM_OK){
		std::cerr << "Environment variables not loaded, CALM_STATUS: " << status << "\n";
	}
	std::string API_KEY    = std::getenv("OPENROUTER_API_KEY");
	std::string MODEL_NAME = std::getenv("NEMOTRON_3_NANO");
	std::string BASE_URL   = std::getenv("BASE_URL");

	calm::ChatModel model(API_KEY, MODEL_NAME, BASE_URL, TEMPERATURE, MAX_TOKENS);
	std::string r = model.invoke("Hello, What is your name?");
	std::cout << r << std::endl;














	return EXIT_SUCCESS;
}
