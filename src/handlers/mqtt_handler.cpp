/**
 * Copyright (c) 2019 - Miguel Leitao. All rights reserved.
 *
 * https://github.com/miguelleitao/mailbridge/
 */

#include <iostream>
#include "mqtt_handler.h"
#include "../util/logging_util.h"

void MqttHandler::handle(SmtpMessage *message) {
    /*
    std::cout << "New email message received." << std::endl
              << "From: " << message->get_sender() << std::endl
              << "To: " << message->get_receiver() << std::endl
              << "Subject: " << message->get_subject() << std::endl
              << "Message: " << message->get_message() << std::endl;
    */

    int pos1 = message->get_sender().find(':');
    int pos2 = message->get_sender().find('@', pos1);
    int len2 = message->get_sender().length() - pos2 - 3;
    
    std::string topic =  message->get_sender().substr(pos2+1, len2) + "/" +
    			 message->get_sender().substr(pos1+2,pos2-pos1-2) + "/" +
    			 message->get_subject(); 
    //log_info("topic: " + topic + ".");
    SendOne(topic.c_str(), message->get_message().c_str(), 1, 0);
    log_info("Handled message using mqtt.");
}
