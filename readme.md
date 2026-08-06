```text 
           | |          
   ___ __ _| |_ __ ___  
  / __/ _` | | '_ ` _ \ 
 | (_| (_| | | | | | | |
  \___\__,_|_|_| |_| |_|
```
`calm` is a minimal C++17 client library for interacting with LLMs. It provides a lightweight abstraction over over model providers' chat completion APIs without bothering with the more complex parts (orchestration, agents, etc) of heavier frameworks.

Some simple features include: 

1.  Simple C++ interface for Chat completions 
2.  HTTP requests via [libcpr/cpr](https://github.com/libcpr/cpr) 
3.  JSON parsing via [nlohmann/json](https://github.com/nlohmann/json) 
4.  Easily extendible to any model provider's API. 

Example / Intended usage is very simple to how some aspects of `langchain_core` work: 

```cpp
calm::ChatModel llm = calm::init_chat_model(
    model = MODEL_NAME, 
    model_provider = PROVIDER_NAME, 
    api_key = API_KEY, 
    base_url = BASE_URL
); 
messages = std::string("Hello!");
calm::ChatMessage response = llm.invoke(messages);
std::cout << response.content << std::endl;
```


##  Roadmap
1.  DONE: ~Safely read environment variables from the  `.env` file~.
2.  DONE: ~Build the first request: figure out what is needed from `libcpr` to build the first GET request to OpenRouter~
3.  UNDERWAY: build `calm::ChatModel` as a wrapper around the OpenRouter API. Include more methods in the `ChatOpenRouter` class which interact with some cool endpoints.  
    
    Figure out how to send individual `std::string messages`  to `ChatModel.invoke()`


The immediate reason to seperate the different model providers into their own `ChatModel` subclasses is that they all probably have their own API endpoints which need to be treated differently (especially when building the JSON payload for each). 

I need to have a  stricter documentation of the status codes of the responses from the OpenRouter API. I need a strict error handling system based on the status codes, right now things are failing silently. This would mean death if anything is built upon this code.


