#include "httplib.h"
#include <iostream>
#include <string>

void handle_post(const httplib::Request& req, httplib::Response& res) {
    if (req.has_param("phrase")) {
        std::string phrase = req.get_param_value("phrase");
        std::cout << "Received phrase: " << phrase << std::endl;
        //!Agregar procesamiento de frase

        // Send a response
        res.set_content("Phrase received: " + phrase, "text/plain");
    } else {
        res.set_content("Invalid request", "text/plain");
    }
}

int main() {
    httplib::Server svr;

    // Serve the static files
    svr.set_mount_point("/", "web");

    // Handle POST requests to / endpoint
    svr.Post("/", [](const httplib::Request& req, httplib::Response& res) {
        handle_post(req, res);
    });

    std::cout << "Server listening on http://localhost:8080" << std::endl;

    svr.listen("localhost", 8080);

    return 0;
}
