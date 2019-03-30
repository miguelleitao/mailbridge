/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_SERVERS_SERVER_H
#define MAILBRIDGE_SERVERS_SERVER_H

#include "../configurations/configuration.h"
#include "../handlers/handler.h"

/**
 * Abstract server.
 */
class Server {
protected:
    Configuration *config;
public:
    /**
     * Server constructor.
     *
     * @param config the configuration to use
     */
    explicit Server(Configuration *config) : config(config) {};

    /**
     * Server destructor.
     */
    virtual ~Server() = default;

    /**
     * Accepts the client at the given socket.
     *
     * @param socket the client socket
     */
    virtual void accept_client(int socket) = 0;

    /**
     * Tries to authenticate the given credentials. Returns true if at least
     * one handler matches, or if there are no handlers configured.
     *
     * @param authentication the credentials to verify
     * @return true if successfully authenticated
     */
    bool authenticate(Authentication *authentication);

    /**
     * Gets the server configuration.
     *
     * @return the configuration
     */
    Configuration *configuration() {
        return this->config;
    }

    /**
     * Handles the given message using the configured handler.
     *
     * @param authentication credentials
     * @param message the message to handle
     */
    void handle(Authentication *authentication, SmtpMessage *message);
};

#endif /* MAILBRIDGE_SERVERS_SERVER_H */