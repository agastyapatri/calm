#include <cstdlib>
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <calm.hpp> 
#include <string> 
#include <cpr/cpr.h>

int main(){
	bool status = calm::load_dotenv(".env");
	if(status != calm::CALM_OK){
		std::cerr << "Environment variables not loaded, CALM_STATUS: " << status << "\n";
	}
	std::string API_KEY    = std::getenv("OPENROUTER_API_KEY");
	std::string MODEL_NAME = std::getenv("NEMOTRON_3_NANO");
	std::string BASE_URL   = std::getenv("BASE_URL");

	std::string chat_completion_endpoint = BASE_URL + "chat/completions";
	json payload = {
		{"max_tokens", 150}, 
		{"messages", {
				{{"content", "You are a helpful assistant."}, {"role", "system"}},
				{{"content", "What is the capital of france"}, {"role", "user"}},

		}},
		{"model", MODEL_NAME}, 
		{"temperature", 0.5}
	};
	std::string json_payload = payload.dump(4);
	cpr::Response r = cpr::Post(
		cpr::Url(chat_completion_endpoint), 
		cpr::Header{
			{"Content-Type", "application/json"},
			{"Authorization", "Bearer " + API_KEY},
		},
		cpr::Body(json_payload)
	);
	std::cout << r.text << std::endl;














	return EXIT_SUCCESS;
}
