/**
 * Copyright (c) 2022 - Miguel Leitao. All rights reserved.
 *
 * https://github.com/miguelleitao/mailbridge/
 */

#ifndef MAILBRIDGE_CONFIGURATIONS_MAIL_CONFIGURATION_H
#define MAILBRIDGE_CONFIGURATIONS_MAIL_CONFIGURATION_H

#include <cstdint>
#include <json.hpp>
#include <string>
#include <utility>

using json = nlohmann::json;

/**
 * Configuration for a Mail handler.
 */
class MailConfiguration {
private:
    std::string mailHostname;
    std::string mailUsername;
    std::string mailPassword;
    int		mailPort;
public:
    /**
     * MailConfiguration constructor.
     *
     * @param channel the channel
     * @param team the team
     * @param webhook the webhook url
     */
     /*
    MailConfiguration(std::string channel, std::string webhook) :
            channel(std::move(channel)), webhook(std::move(webhook)) {};
*/

    MailConfiguration(json options) {
        mailHostname = options["mailHostname"].get<std::string>();
        mailUsername = options["mailUsername"].get<std::string>();
        mailPassword = options["mailPassword"].get<std::string>();
        mailPort     = options["mailPort"].get<int>();

std::cout << "leu mail config\n ";
    }
    
    /**
     * MailConfiguration destructor.
     */
    ~MailConfiguration() = default;

    /**
     * Gets the Mail server hostname.
     *
     * @return hostname
     */
    std::string get_mailHostname() {
        return this->mailHostname;
    }

    /**
     * Gets the Mail username.
     *
     * @return username
     */
    std::string get_mailUsername() {
        return this->mailUsername;
    }
    
    /**
     * Gets the Mail password.
     *
     * @return password
     */
    std::string get_mailPassword() {
        return this->mailPassword;
    }
    
    /**
     * Gets the Mail server port.
     *
     * @return port
     */
    int get_mailPort() {
        return this->mailPort;
    }
};

#endif /* MAILBRIDGE_CONFIGURATIONS_MAIL_CONFIGURATION_H */
