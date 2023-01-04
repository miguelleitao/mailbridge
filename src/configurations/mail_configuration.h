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
#include "configuration.h"

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
    std::string mailReceiver;
    std::string mailSender;
    std::string mailReceiverName;
    std::string mailSenderName;
    std::string mailSubject;
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
        // defaults
        mailHostname = "localhost";
        mailPort = 443;
        mailHostname     = get_config_item(mailHostname,     options, "mailHostname");
        mailUsername     = get_config_item(mailUsername,     options, "mailUsername");
        mailPassword     = get_config_item(mailPassword,     options, "mailPassword");
        mailPort         = get_config_item(mailPort,         options, "mailPort");
        mailReceiver     = get_config_item(mailReceiver,     options, "mailReceiver");
        mailSender       = get_config_item(mailSender,       options, "mailSender");
        mailReceiverName = get_config_item(mailReceiverName, options, "mailReceiverName");
        mailSenderName   = get_config_item(mailSenderName,   options, "mailSenderName");    
        mailSubject      = get_config_item(mailSubject,      options, "mailSubject");
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
    
    /**
     * Gets the Mail Receiver.
     *
     * @return receiver
     */
    std::string get_mailReceiver() {
        return this->mailReceiver;
    }
    /**
     * Gets the Mail Receiver Name.
     *
     * @return receiver name
     */
    std::string get_mailReceiverName() {
        return this->mailReceiverName;
    }
    /**
     * Gets the Mail Sender.
     *
     * @return sender
     */
    std::string get_mailSender() {
        return this->mailSender;
    }
    /**
     * Gets the Mail Sender Name.
     *
     * @return sender name
     */
    std::string get_mailSenderName() {
        return this->mailSenderName;
    }
    /**
     * Gets the Mail Subject.
     *
     * @return subject
     */
    std::string get_mailSubject() {
        return this->mailSubject;
    }
};

#endif /* MAILBRIDGE_CONFIGURATIONS_MAIL_CONFIGURATION_H */
