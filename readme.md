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
calm::ChatModel llm = calm::init_chat_model(model = MODEL_NAME, model_provider = PROVIDER_NAME, api_key = API_KEY, base_url = BASE_URL); 
messages = std::string("Hello!");
calm::ChatResponse response = llm.invoke(messages);
std::cout << response.content << std::endl;
```

