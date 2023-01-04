/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <fstream>
#include <json.hpp>
#include <iostream>
#include "configuration.h"
#include "authentication.h"
#include "../handlers/handler.h"
#include "../handlers/slack_handler.h"
#include "../handlers/stdout_handler.h"
#include "../handlers/mqtt_handler.h"
#include "../handlers/mail_handler.h"
#include "../util/logging_util.h"

using json = nlohmann::json;

/**
 * Creates a Slack handler from the specified options.
 *
 * @param options the handler options
 * @return the Slack handler
 */
SlackHandler *create_slack_handler(json options);

/**
 * Creates a Mqtt handler from the specified options.
 *
 * @param options the handler options
 * @return the Mqtt handler
 */
MqttHandler *create_mqtt_handler(json options);

/**
 * Creates a Mail handler from the specified options.
 *
 * @param options the handler options
 * @return the Mail handler
 */
MailHandler *create_mail_handler(json options);
/*
std::string get_config_string(std::string &var, json block, std::string name, bool required) {
    if ( block[name] != nullptr )
    	var = block[name].get<std::string>();
    if ( required ) std::cout << "Error: Required parameter '" << name << "' not found.\n";
    return var;
}
*/

/*
template<typename T>
    T get_config_item(T &var, json block, std::string name, bool required) {
        if ( block[name] != nullptr )
    	    var = block[name].get<std::string>();
        if ( required ) std::cout << "Error: Required parameter '" << name << "' not found.\n";
        return var;
    }
*/


std::string get_config_string(auto &var, json block, std::string name, bool required) {
    typeof(var) c;
    if ( block[name] != nullptr )
    	var = block[name].get<std::string>();
    if ( required ) std::cout << "Error: Required parameter '" << name << "' not found.\n";
    return var;
}
/*
std::string get_config_string_v2(std::string &var, json block, std::string name, bool required) {
    return get_config_item(var, block, name, required);
}

int get_config_int(int &var, json block, std::string name, bool required) {
    return get_config_item(var, block, name, required);
}
*/
Configuration::Configuration(const std::string &file) {
    std::ifstream file_stream(file);
    json j;
    file_stream >> j;

    this->name = j["name"].get<std::string>();
    name = get_config_item(name, j, "name", true);
    this->port = j["port"].get<std::uint_fast16_t>();

    this->handlers = std::map<Authentication *, Handler *>();

    json handlers_raw = j["handlers"];
    for (auto &handler_raw : handlers_raw) {
        //std::string handler_name = handler_raw["handler"].get<std::string>();
        std::string handler_name = get_config_string(handler_name, handler_raw, "handler", true);
        json handler_options = handler_raw["options"];
        //std::string password = handler_raw["password"].get<std::string>();
        std::string password = get_config_string(password, handler_raw, "password");
        //handler_raw["password"].get<std::string>();
        std::string username = get_config_string(username, handler_raw, "username");
        //handler_raw["username"].get<std::string>();

        auto *authentication = new Authentication(username, password);

        if (handler_name == "slack") {
            this->handlers.insert({authentication, create_slack_handler(handler_options)});
        } else if (handler_name == "stdout") {
            this->handlers.insert({authentication, new StdoutHandler()});
        } else if (handler_name == "mqtt") {
            MqttConfiguration *configuration = new MqttConfiguration(handler_options);
            this->handlers.insert({authentication, new MqttHandler(configuration)});
        } else if (handler_name == "mail") {
            MailConfiguration *configuration = new MailConfiguration(handler_options);
            this->handlers.insert({authentication, new MailHandler(configuration)});
        } else {
            throw_error("Unknown handler: " + handler_name + ".");
        }
    }
}

SlackHandler *create_slack_handler(json options) {
    std::string channel = options["channel"].get<std::string>();
    std::string webhook = options["webhook"].get<std::string>();

    auto *slack_configuration = new SlackConfiguration(channel, webhook);

    return new SlackHandler(slack_configuration);
}

MqttHandler *create_mqtt_handler(json options) {

    auto *mqtt_configuration = new MqttConfiguration(options);

    return new MqttHandler(mqtt_configuration);
}

MailHandler *create_mail_handler(json options) {

    auto *mail_configuration = new MailConfiguration(options);

    return new MailHandler(mail_configuration);
}
