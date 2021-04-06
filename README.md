# mailbridge
[![.github/workflows/build.yml](https://github.com/thepieterdc/mailbridge/actions/workflows/build.yml/badge.svg)](https://github.com/thepieterdc/mailbridge/actions/workflows/build.yml)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7cd4042a1c8e42828b7182d7e5580564)](https://www.codacy.com/project/thepieterdc/mailbridge/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=thepieterdc/mailbridge&amp;utm_campaign=Badge_Grade_Dashboard)

## Usage
If no configuration file is provided, the mailserver listens on port `1025, any authentication credentials are ignored and nothing happens when an incoming mail is received.

```
./mailbridge
```

A configuration file can be provided using the `-f` flag. This must be a json file, see below.

```
./mailbridge -f config.json
```

## Configuration file
- **handlers:** Configurable actions that should be executed when receiving new incoming emails. Multiple handlers can be configured, the `username` and `password` fields are used to decide which handler to execute. You can use the same username/password combination multiple times if one emails should be processed by multiple handlers. If this is the case, each handler will be invoked in the same order as they are declared. Consult the conf/ folder for more information about the available handlers.
- **name:** The name of the mailserver, this can be anything and will be used when answering to `HELO/EHLO` requests.
- **port:** The port that this mailserver should run on.

### Example configuration
```json
{
    "handlers": [{
        "handler": "slack",
        "username": "some_user",
        "password": "some_password",
        "options": {
            "channel": "some_channel_name",
            "webhook": "https://hooks.slack.com/services/a/b/c"
        }
    }],
    "name": "thepieterdc.github.io",
    "port": 25
}
```

## Usage in projects

### Ruby-on-Rails
config/environments/development.rb
```ruby
config.action_mailer.delivery_method = :smtp
config.action_mailer.smtp_settings = {
    address: 'localhost',
    authentication: :plain,
    password: 'my_password',
    port: 2525,
    user_name: 'my_username'
}
```