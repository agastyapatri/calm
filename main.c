#include <curl/curl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <calm.h> 
#include <string.h>
#define PATH_TO_ENV ".env"




int main(void) {
    char *api_key = NULL;
    calm_status status = calm_env_get(".env", "OPENROUTER_API_KEY", &api_key);
    if (status != CALM_OK) {
        fprintf(stderr, "failed to load API key: %d\n", status);
        return 1;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "curl_easy_init failed\n");
        free(api_key);
        return 1;
    }

    calm_buffer buf;
    buf.data = NULL;
    buf.size = 0;

    const char *json_body =
        "{"
        "\"model\": \"nvidia/nemotron-3-nano-30b-a3b:free\","
        "\"messages\": [{\"role\": \"user\", \"content\": \"What is the capital of France?\"}]"
        "}";

    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, "https://openrouter.ai/api/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform failed: %s\n", curl_easy_strerror(res));
    } else {
        printf("%s\n", buf.data);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(buf.data);
    free(api_key);

    return 0;
}
