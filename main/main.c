#include <stdio.h>
#include "esp_wifi.h"
#include "esp_http_server.h"


esp_netif_t * wifi_init_softap() {
    esp_netif_t * esp_netif_ap = esp_netif_create_default_wifi_ap();

    return esp_netif_ap;
};


esp_err_t hello_endpoint_handler(httpd_req_t * req) {
    return ESP_OK;
};


static httpd_uri_t hello_endpoint = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = hello_endpoint_handler,
    .user_ctx = NULL
};


httpd_handle_t start_http_server() {
    httpd_config_t server_config = HTTPD_DEFAULT_CONFIG();

    server_config.server_port = 2137;


    httpd_handle_t handle = NULL;

    if (httpd_start(&handle, &server_config) == ESP_OK) {
        printf("successfully created http server\n");
        if (httpd_register_uri_handler(handle, &hello_endpoint) == ESP_OK) {
            printf("successfully registered hello endpoint\n");
        };
    };

    return handle;
}


void stop_http_server() {

}



void app_main(void) {
    printf("DUPAAAAAAA\n");

    esp_netif_t * net_handler = wifi_init_softap();

    printf("net handler: %d\n", (int)net_handler);

    esp_netif_destroy_default_wifi(net_handler);
    /*
    httpd_handle_t server = start_http_server();

    if (server == NULL) {
        printf("could not start the server\n");
    }
    */
}
