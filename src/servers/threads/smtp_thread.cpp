/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <cstring>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include "base64.hpp"
#include "smtp_thread.h"
#include "../../util/string_util.h"
#include "../../util/logging_util.h"

void SmtpThread::client_send(const std::string &data) {
    auto length = static_cast<size_t>(data.length());
    send(this->client_fd, data.c_str(), length, 0);
}

void SmtpThread::greet() {
    client_send("220 " + this->server.configuration()->get_name() + "\n");
}

void SmtpThread::handle_auth() {
    auto authentication_line = split_string(this->last_line, " ");
    auto authentication_mechanism = authentication_line.at(1);

    if (authentication_mechanism != "PLAIN") {
        throw_error("Unsupported authentication mechanism: " + authentication_mechanism);
    }

    auto authentication_data_raw = base64_decode(authentication_line.at(2));
    auto authentication_data = split_string(authentication_data_raw, '\0');

    auto username = authentication_data.at(1);
    auto password = authentication_data.at(2);

    this->authentication = new Authentication(username, password);

    if (this->server.authenticate(this->authentication)) {
        client_send("235 2.7.0  Authentication Succeeded\n");
    } else {
        client_send("535 5.7.8  Authentication credentials invalid\n");
    }
}

void SmtpThread::handle_data() {
    client_send("354 Start mail input, finish by sending <CRLF>.<CRLF>\n");

    std::stringstream data;

    char buffer[1024 + 1] = {0};
    ssize_t buffersize = 0;

    while (true) {
        if (buffersize == 0) {
            buffersize = recv(this->client_fd, buffer, 1024, 0);
        }

        if (strcmp(buffer, ".\r\n") == 0) {
            break;
        }

        for (int i = 0; i < buffersize; ++i) {
            data << buffer[i];
            if (buffer[i] == '\n') {
                char remaining[1024 + 1] = {0};
                std::copy(buffer + i + 1, buffer + buffersize, remaining);
                memcpy(buffer, remaining, 1024);
                buffersize -= (i + 1);
                break;
            }
        }
    }

    std::string data_str(data.str());

    std::string subject_start(data_str.substr(data_str.find("\r\nSubject: ") + 11));
    this->message->set_subject(subject_start.substr(0, subject_start.find("\r\n")));

    std::string message_start(subject_start.substr(subject_start.find("\r\n\r\n") + 4));
    this->message->set_message(message_start.substr(0, message_start.length() - 2));

    client_send("250 OK\n");
}

void SmtpThread::handle_helo() {
    this->helo_name = this->last_line.substr(5);
    client_send("250 " + this->server.configuration()->get_name() + "\n");
}

void SmtpThread::handle_mail() {
    size_t startpos = this->last_line.find('<');
    size_t endpos = this->last_line.find('>');
    std::string sender(this->last_line.substr(startpos + 1, endpos - startpos - 1));

    this->message->set_sender(sender);

    client_send("250 OK\n");
}

void SmtpThread::handle_quit() {
    client_send("221 BYE\n");
    this->active = false;
}

void SmtpThread::handle_rcpt() {
    size_t startpos = this->last_line.find('<');
    size_t endpos = this->last_line.find('>');
    std::string receiver(this->last_line.substr(startpos + 1, endpos - startpos - 1));

    this->message->set_receiver(receiver);

    client_send("250 OK\n");
}

std::string SmtpThread::receive() {
    char buffer[1024 + 1] = {0};
    recv(this->client_fd, &buffer, 1024, 0);
    this->last_line = std::string(buffer);
    return this->last_line;
}