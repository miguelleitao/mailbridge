/**
 * Copyright (c) 2022 - Miguel Leitao. All rights reserved.
 *
 * https://github.com/miguelleitao/mailbridge/
 */

#ifndef MAILBRIDGE_HANDLERS_MQTT_HANDLER_H
#define MAILBRIDGE_HANDLERS_MQTT_HANDLER_H

#include "handler.h"
#include "mosquitto.h"
#include "../configurations/mqtt_configuration.h"
#include "../messages/smtp_message.h"

/**
 * Handles received incoming emails by posting them to stdout.
 */
class MqttHandler : public Handler {
private:
    struct mosquitto *mosq;
    MqttConfiguration *config;
public:
    /**
     * MqttHandler constructor.
     */
     /*
    MqttHandler(MqttConfiguration *configuration) : Handler() {
        mosquitto_lib_init();      
    };*/
    explicit MqttHandler(MqttConfiguration *configuration) : Handler(), config(configuration) {
        mosquitto_lib_init();
    };
    void Init() {
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
		fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
		return;
	}
	fprintf(stderr, "Connecting to %s:%d\n", hostname.c_str(), port);
        mosquitto_loop_start(	mosq	);
    }
    void on_connect(struct mosquitto *mosq, void *obj, int reason_code) {
   
        if ( reason_code != 0 ) {
            mosquitto_disconnect(mosq);
        }
        // Once connected, consider subscribe to some mqtt topics...
        //int rc = mosquitto_subscribe(mosq, NULL, "mailbridge/cmd/#", 1);
    }
    
    void Send(const char *topic, const char* msg, int qos, int retain) {
        char fullTopic[640];
        sprintf(fullTopic, "%s/%s", "mailbridge/message", topic);
        int rc = mosquitto_publish(mosq, NULL, fullTopic, strlen(msg), msg, qos, retain);
        if ( rc != MOSQ_ERR_SUCCESS ) {
        	fprintf(stderr, "Error publishing to MQTT broker: %s\n", mosquitto_strerror(rc));
        }
    }
    
    void Disconnect() {
    	mosquitto_disconnect(mosq);
    	mosquitto_loop_stop(mosq, false);
    }

    void SendOne(const char *topic, const char* msg, int qos, int retain) {
        Init();
        Send(topic, msg, qos, retain);
        Disconnect();
    }
    /**
     * MqttHandler destructor.
     */
    //~MqttHandler() override = default;
    ~MqttHandler() {
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
    }

    void handle(SmtpMessage *message) override;
};

#endif /* MAILBRIDGE_HANDLERS_MQTT_HANDLER_H */
