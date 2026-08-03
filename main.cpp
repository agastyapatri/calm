#include <iostream> 
#include <fstream> 
#include <vector> 
#include <json.hpp> 
using json = nlohmann::json;
int main(){
	std::ifstream file("response.json", std::ios::in);
	json data = json::parse(file);
	std::cout << data << std::endl;







	return 0;
}
