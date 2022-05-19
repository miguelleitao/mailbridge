# Mqtt handler

The Mqtt handler can be used to send incoming mails to a MQTT broker. It has the following configuration options:

- **mqttHostname:** The IP address or hostname where the MQTT broker is running.
- **mqttUsername:** The username used for authentication when connecting to the destination MQTT broker.
- **mqttPassword:** The password used for authentication when connecting to the destination MQTT broker.
- **mqttPort:** The TCP destination port number to connect to the MQTT broker.

## Example configuration

```json
{
    "handlers": [{
        "username": "some_user",
        "password": "some_password",
        "handler": "mqtt",
        "options": {
            "mqttHostname": "broker.domain.name",
            "mqttUsername": "broker_user",
            "mqttPassword": "broker_password.",
            "mqttPort": 1883
        }
    }],
    "name": "thepieterdc.mailbridge.local",
    "port": 2525
}
```
