/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_SERVERS_THREADS_SMTP_THREAD_H
#define MAILBRIDGE_SERVERS_THREADS_SMTP_THREAD_H

#include "../smtp_server.h"

/**
 * A thread that can be used to communicate to a client and keep track of the
 * exchanged messages.
 */
class SmtpThread {
private:
    bool active;
    Authentication *authentication;
    int client_fd;
    std::string helo_name;
    std::string last_line;
    SmtpMessage *message;
    SmtpServer server;

    /**
     * Sends a line to the client.
     *
     * @param data data to send
     */
    void client_send(const std::string &data);

public:
    /**
     * SmtpThread constructor.
     *
     * @param srv the server instance
     * @param client the client socket
     */
    SmtpThread(SmtpServer &srv, int client) : active(true), authentication(nullptr), client_fd(client), server(srv) {
        this->message = new SmtpMessage();
    }

    /**
     * SmtpThread destructor.
     */
    ~SmtpThread() {
        delete this->authentication;
        delete this->message;
    }

    /**
     * Gets the authentication.
     *
     * @return the authentication
     */
    Authentication *get_authentication() {
        return this->authentication;
    }

    /**
     * Gets the received message.
     *
     * @return the received message
     */
    SmtpMessage *get_message() {
        return this->message;
    }

    /**
     * Greets the client.
     */
    void greet();

    /**
     * Handles the AUTH command.
     */
    void handle_auth();

    /**
     * Handles the DATA command.
     */
    void handle_data();

    /**
     * Handles the HELO/EHLO command.
     */
    void handle_helo();

    /**
     * Handles the MAIL command.
     */
    void handle_mail();

    /**
     * Handles the QUIT command.
     */
    void handle_quit();

    /**
     * Handles the RCPT command.
     */
    void handle_rcpt();

    /**
     * Gets whether the thread is still in use.
     *
     * @return true if the thread is active
     */
    bool is_active() {
        return this->active;
    }

    /**
     * Receives a line from the client and stores it in the last_line variable.
     *
     * @return the data received
     */
    std::string receive();
};

#endif /* MAILBRIDGE_SERVERS_THREADS_SMTP_THREAD_H */