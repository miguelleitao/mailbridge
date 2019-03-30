/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "smtp_server.h"
#include "threads/smtp_thread.h"

void SmtpServer::accept_client(int socket) {
    SmtpThread client(*this, socket);
    client.greet();

    while (client.is_active()) {
        std::string line = client.receive();
        std::string command = line.substr(0, 4);

        if (command == "AUTH") {
            client.handle_auth();
        } else if (command == "DATA") {
            client.handle_data();
        } else if (command == "HELO" || command == "EHLO") {
            client.handle_helo();
        } else if (command == "MAIL") {
            client.handle_mail();
        } else if (command == "QUIT") {
            client.handle_quit();
        } else if (command == "RCPT") {
            client.handle_rcpt();
        } else if (line.empty()) {
            break;
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
            break;
        }
    }

    close(socket);

    this->handle(client.get_authentication(), client.get_message());
}