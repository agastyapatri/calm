#   CaLM 
`calm` is a small C library for making chat completion requests to [OpenRouter](https://openrouter.ai). `calm` uses `libcurl` and `cJSON` as its main dependencies.


## Project Structure

```text 
calm/ 
    - src/
        - cJSON.h 
        - cJSON.c 
        - .... other source files.
    - main.c 
    - readme.md
    - CMakeLists.txt 
```

##  Roadmap
1.  **Raw HTTP, no libraries**
-   Write a single `main.c` file that makes one hardcoded `POST` request to OpenRouter using libcurl directly. 
-   Learn: `curl_easy_init/curl_easy_setopt/curl_easy_perform`, headers via `curl_slist`, the CURLOPT_WRITEFUNCTION callback and how libcurl response bytes are streamed back. 
-   Goal: see a real API response on the screen. No structure yet.

2.  **Parse the JSON Response** 
-   Feed that raw JSON into cJSON and pull out the message content. 
-   Learn: cJSON's parse/get-object-item API, and JSON ownership rules (what you must `Delete()`).
-   Goal: print out the model's reply text, cleanly. 

3.  **Encapsulate: The `client` struct** 
-   Wrap the curl handle + API key + model into an opaque `calm_client` with `calm_client_create()` and `calm_client_destroy()`.
-   Learn the opaque pointer pattern, heder/implementation separation, why the curl handle must persist across all calls instead of being recreated each time. 
-   Goal: `main.c` only includes `calm.h` and never touches curl or cJSON directly.

4.  **Clean request/response types** 
-   Design a `calm_response` struct with content, error, http_status as the return type of the chat function. 
-   Learn how to design an error handling convention across a C API boundary (no exceptions - sentinel values, out params or struct-with-error-field).

5.  **Hardening (stretch)** 
-   Timeouts, retry on transient failure, streaming responses, thread safety notes. 
-   Learn `CURLOPT_TIMEOUT`, introduce yourself to `curl_multi`. 



##  **Notes** 
Things that I need to know before diving head-first into code. 
### **HTTP and `libcurl`** 
1.  A HTTP request has a few parts: 
-   **Method** : `POST` will be used to send data / trigger something on the server. `GET` might be used to retrieve something from the server. 
-   **URL**: OpenRouter Base URL. 
-   **Headers:** metadata about the request, sent as `key:value` pairs.  `Authorization: Bearer <api-key>` proves the authenticity of the client making the request and `Content-Type: application/json` tells the server that the body of the request is a JSON payload.
-   **Body:** The actual JSON payload describing the request being made. 

2.  The server sends back a HTTP response: a status code (200 meaning success, 401 meaning bad auth, etc.), it's own headers and body, which in this case will be JSON containing the model's reply.


3.  `libcurl`'s API is built around once core object, a `CURL*` handle, which is configured step by step via `curl_easy_setopt(handle, OPTION, value)` calls. This handle is then fired with `curl_easy_perform(handle)`. 


4.  `libcurl` doesn't return a string when `curl_easy_perform()` finishes. Instead, *the user gives it a callback function *before* the call, and libcurl invokes that callback itself, possibly multiple times, as response data arrives*. The user is responsible for accumulating the incoming data into their own buffer. This pattern is found in many libraries (HTTP libs, GUI toolkits, audio APIs - anywhere a lower layers needs to hand data back to the user asynchronously.)




### **Error handling**
`calm` uses a set of error codes defined in `enum CALM_STATUS`. It is guaranteed that upon failure, the target structure will be safe to inspect and will have the necessary parameters be `NULL`. 

    Upon any non-`CALM_OK` status from `calm_client_chat`, `content` is guaranteed `NULL` for `struct calm_response`. `error` and `http_status` are populated whenever they are known.
--------------------------

### **Client**
`calm_client`: is the object that represents one configured connection to OpenRouter. It is the structure that remembers the user API key, model name, base url and the resuable curl handle, so that curl is not being initialized repeatedly. Think of it as an `fopen()` for the API connection. 

`calm_client` is being made an *opaque pointer* by making sure that the header file only contains the forward declaration of the struct. The user *must* go throught `calm_client_create()`, `calm_client_chat()`, `calm_client_destroy()`. This enforces necessary information-hiding at the compiler level. In `main.c` or any other translation unit, the user **cannot** call `client->api_key`. 

This is why `calm_client_create` has to operate on a pointer (`calm_client** out`) rather than return a struct by value.

#### `libcurl` and function pointers. 
A function pointer is a variable that holds the memory address of a function instead of a type or a struct. The syntax to declare a function pointer is: 
```c
type (*variable_name)(type)

int (*ptr)(int) = NULL; //  a pointer to a function which takes in an int and returns an int.
```
A function pointer does not really care which function it points to as long as the function has the correct signature. 

**Why does this matter for `libcurl`**: `curl_easy_setopt(handle CURLOPT_WRITEFUNCTION, callback_function)` uses the user defined `callback_function` and calls it multiple times internally, whenever data arrives. `callback_function` must have the signature that `libcurl` expects.  

The function signature expected by `curl_easy_setopt` is: `size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);
`
-   `void* contents`: pointer to the chunk of response data that libcurl just received. 
-   `size_t size, nmbem`: the actual byte count of the incoming chunk is `size * nmemb`. 
-   `void* userp`: This is the user provided pointer that libcurl returns back on every call so that the user can accumulate the data across multiple calls. 
-   The function must return the number of bytes actually processed. 
























