/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_CONFIGURATIONS_CONFIGURATION_H
#define MAILBRIDGE_CONFIGURATIONS_CONFIGURATION_H

#include <cstdint>
#include <map>
#include <string>
#include <json.hpp>
#include "authentication.h"
#include "../handlers/handler.h"

using json = nlohmann::json;

/**
 * Application configuration.
 */
class Configuration {
private:
    std::map<Authentication *, Handler *> handlers;
    std::string name;
    std::uint_fast16_t port;
public:
    /**
     * Configuration constructor.
     *
     * @param file the path to the configuration file
     */
    explicit Configuration(const std::string &file);

    /**
     * Configuration destructor.
     */
    ~Configuration() = default;

    /**
     * Gets the configured handlers.
     *
     * @return the configured handlers
     */
    std::map<Authentication *, Handler *> get_handlers() {
        return this->handlers;
    }

    /**
     * Gets the name of the mailserver.
     *
     * @return the hostname
     */
    std::string get_name() {
        return this->name;
    }

    /**
     * Gets the port the application should listen on.
     *
     * @return the port
     */
    std::uint_fast16_t get_port() {
        return this->port;
    }
};

#endif /* MAILBRIDGE_CONFIGURATIONS_CONFIGURATION_H */