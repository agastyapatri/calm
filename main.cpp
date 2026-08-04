#include <cstdlib>
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <calm.hpp> 
#include <string> 


int main(){
	bool status = calm::load_dotenv(".env");
	if(status != calm::CALM_OK){
		std::cerr << "Environment variables not loaded, CALM_STATUS: " << status << "\n";
	}
	std::string API_KEY    = std::getenv("OPENROUTER_API_KEY");
	std::string MODEL_NAME = std::getenv("GEMMA_4_31B");
	std::string BASE_URL   = std::getenv("BASE_URL");

	calm::ChatModel model(API_KEY, MODEL_NAME, BASE_URL);
	std::cout << model.base_url() << std::endl;
	std::cout << model.model_name() << std::endl;
	







	return EXIT_SUCCESS;
}
