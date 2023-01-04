/**
 * Copyright (c) 2022 - Miguel Leitao. All rights reserved.
 *
 * https://github.com/miguelleitao/mailbridge/
 */

#ifndef MAILBRIDGE_HANDLERS_MAIL_HANDLER_H
#define MAILBRIDGE_HANDLERS_MAIL_HANDLER_H

#include "handler.h"
#include "../configurations/mail_configuration.h"
#include "../messages/smtp_message.h"

#define SMTP_OPENSSL
#include "smtpclient.h"


/**
 * Handles received incoming emails by forward them to smtp server.
 */
class MailHandler : public Handler {
private:
    MailConfiguration *config;
public:
    /**
     * MailHandler constructor.
     */
     /*
    MailHandler(MailConfiguration *configuration) : Handler() {
             
    };*/
    explicit MailHandler(MailConfiguration *configuration) : Handler(), config(configuration) {
        
    };

  
    void Send(SmtpMessage *msg);

    void SendOne(SmtpMessage *msg) ;
    /**
     * MailHandler destructor.
     */
    //~MailHandler() override = default;
    ~MailHandler() {
    }

    void handle(SmtpMessage *message) override;
};

#endif /* MAILBRIDGE_HANDLERS_MAIL_HANDLER_H */
