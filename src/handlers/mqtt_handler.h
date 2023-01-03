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
 * Handles received incoming emails by posting them to MQTT.
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
    void Init();
    void on_connect(struct mosquitto *mosq, void *obj, int reason_code) {
   
        if ( reason_code != 0 ) {
            mosquitto_disconnect(mosq);
        }
        // Once connected, consider subscribe to some mqtt topics...
        //int rc = mosquitto_subscribe(mosq, NULL, "mailbridge/cmd/#", 1);
    }
    
    void Send(const char *topic, const char* msg, int qos, int retain);
    
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
