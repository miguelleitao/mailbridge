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

    std::string topic = "";
    int pos2 = message->get_sender().find('@');
    if ( pos2 ) {
        int len2 = message->get_sender().length() - pos2 - 3;
        topic = message->get_sender().substr(pos2+1, len2+2) + "/" +
                message->get_sender().substr(0,pos2);
    }
    else {
	topic =  message->get_sender();
    }
    topic += "/" + message->get_subject(); 
    SendOne(topic.c_str(), message->get_message().c_str(), 1, 0);
    log_info("Handled message using mqtt.");
}

void MqttHandler::Send(const char *topic, const char* msg, int qos, int retain) {
        char fullTopic[640];
        sprintf(fullTopic, "%s/%s", "mailbridge/message", topic);
        int rc = mosquitto_publish(mosq, NULL, fullTopic, strlen(msg), msg, qos, retain);
        if ( rc != MOSQ_ERR_SUCCESS ) {
        	fprintf(stderr, "Error publishing to MQTT broker: %s\n", mosquitto_strerror(rc));
        }
}

void MqttHandler::Init() {
        mosq = mosquitto_new(NULL, true, NULL);
        if ( ! mosq ) {
            std::cout << "Error";
            exit(1);
        }
	
	std::string username = config->get_mqttUsername();
	std::string password = config->get_mqttPassword();
	//printf("Using '%s' '%s'\n", username.c_str(), password.c_str());
	mosquitto_username_pw_set(mosq, username.c_str(), password.c_str());

	/* Connect to MQTT broker on specified port, with a keepalive of 60 seconds.
	 * This call makes the socket connection only, it does not complete the MQTT
	 * CONNECT/CONNACK flow, you should use mosquitto_loop_start() or
	 * mosquitto_loop_forever() for processing net traffic. */
	std::string hostname = config->get_mqttHostname();
	int port = config->get_mqttPort();
	int rc = mosquitto_connect(mosq, hostname.c_str(), port, 60);
	if(rc != MOSQ_ERR_SUCCESS){
		mosquitto_destroy(mosq);
		fprintf(stderr, "Error connecting to MQTT broker '%s': %s\n", hostname.c_str(), mosquitto_strerror(rc));
		return;
	}
	fprintf(stderr, "Connecting to %s:%d\n", hostname.c_str(), port);
        mosquitto_loop_start(mosq);
}
