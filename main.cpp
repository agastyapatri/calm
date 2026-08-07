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
	std::string MODEL_NAME = std::getenv("GEMMA_4_31B");
	std::string BASE_URL   = std::getenv("BASE_URL");

	calm::Model model(API_KEY, MODEL_NAME, BASE_URL, TEMPERATURE, MAX_TOKENS);
	calm::Response r = model.invoke("Hello, What is your name?");
















	return EXIT_SUCCESS;
}
