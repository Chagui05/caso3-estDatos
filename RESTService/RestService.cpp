#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace web::http::client;

http_listener listener("http://localhost:8080");

void handle_post(http_request request)
{
    auto response = json::value::object();
    response[U("status")] = json::value::string(U("success"));

    // Get the content of the request

    request.extract_json().then([&response, &request](json::value body) {
        // Get the value of the textbox
        auto textbox_value = body[U("textbox")].as_string();

        // Convert narrow string to wide string
        std::wstring wide_textbox_value(textbox_value.begin(), textbox_value.end());

        // Print the value of the textbox to the console
        std::wcout << L"Textbox value: " << wide_textbox_value << std::endl;

        // You can send a response back to the client if needed
        // response[U("received")] = json::value::string(textbox_value);
        // request.reply(status_codes::OK, response);
    });

    request.reply(status_codes::OK, response);
}

int main()
{
    listener.support(methods::POST, handle_post);

    try
    {
        listener.open().wait();
        std::wcout << L"Listening for requests at: " << listener.uri().to_string().c_str() << std::endl;

    // Uncomment the following lines if you want to open a web page to interact with your service
    utility::string_t url = U("http://localhost:8080");
    uri_builder uri(url);
    uri.append_path(U("index.html"));

    http_client client(uri.to_uri());
    client.request(web::http::methods::GET).then([](web::http::http_response response) {
        return response;
    }).wait();

        while (true);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
