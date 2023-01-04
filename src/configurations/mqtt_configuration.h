/**
 * Copyright (c) 2022 - Miguel Leitao. All rights reserved.
 *
 * https://github.com/miguelleitao/mailbridge/
 */

#ifndef MAILBRIDGE_CONFIGURATIONS_MQTT_CONFIGURATION_H
#define MAILBRIDGE_CONFIGURATIONS_MQTT_CONFIGURATION_H

#include <cstdint>
#include <json.hpp>
#include <string>
#include <utility>
#include "configuration.h"

using json = nlohmann::json;


/**
 * Configuration for a Mqtt handler.
 */
class MqttConfiguration {
private:
    std::string mqttHostname;
    std::string mqttUsername;
    std::string mqttPassword;
    int		mqttPort;
public:
    /**
     * MqttConfiguration constructor.
     *
     * @param channel the channel
     * @param team the team
     * @param webhook the webhook url
     */
     /*
    MqttConfiguration(std::string channel, std::string webhook) :
            channel(std::move(channel)), webhook(std::move(webhook)) {};
*/

    MqttConfiguration(json options) {
        // defaults
        mqttHostname = "localhost";
        mqttPort = 1883;
        
        // Get config values
        mqttHostname = get_config_item(mqttHostname, options, "mqttHostname");
        mqttUsername = get_config_item(mqttUsername, options, "mqttUsername");
        mqttPassword = get_config_item(mqttPassword, options, "mqttPassword");
        mqttPort     = get_config_item(mqttPort,     options, "mqttPort");
    }
    
    /**
     * MqttConfiguration destructor.
     */
    ~MqttConfiguration() = default;

    /**
     * Gets the Mqtt hostname.
     *
     * @return hostname
     */
    std::string get_mqttHostname() {
        return this->mqttHostname;
    }

    /**
     * Gets the Mqtt username.
     *
     * @return username
     */
    std::string get_mqttUsername() {
        return this->mqttUsername;
    }
    
    /**
     * Gets the Mqtt password.
     *
     * @return password
     */
    std::string get_mqttPassword() {
        return this->mqttPassword;
    }
    
    /**
     * Gets the Mqtt port.
     *
     * @return port
     */
    int get_mqttPort() {
        return this->mqttPort;
    }
};

#endif /* MAILBRIDGE_CONFIGURATIONS_MAIL_CONFIGURATION_H */
