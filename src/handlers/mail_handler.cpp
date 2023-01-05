/**
 * Copyright (c) 2019 - Miguel Leitao. All rights reserved.
 *
 * https://github.com/miguelleitao/mailbridge/
 */

#include <iostream>
#include "mail_handler.h"
#include "../util/logging_util.h"

void MailHandler::handle(SmtpMessage *message) {
    /*
    std::cout << "New email message received." << std::endl
              << "From: " << message->get_sender() << std::endl
              << "To: " << message->get_receiver() << std::endl
              << "Subject: " << message->get_subject() << std::endl
              << "Message: " << message->get_message() << std::endl;
    */
    SendOne(message);
    log_info("Handled message using mail.");
}

void MailHandler::Send(SmtpMessage *msg) {        
    #define MAIL_SERVER              config->get_mailHostname().c_str()
    #define MAIL_PORT                std::to_string(config->get_mailPort()).c_str()
    #define MAIL_CONNECTION_SECURITY SMTP_SECURITY_TLS
    #define MAIL_FLAGS               ( SMTP_DEBUG          | \
                                       SMTP_NO_CERT_VERIFY )     /* Do not verify cert. */
    #define MAIL_CAFILE              NULL
    #define MAIL_AUTH                SMTP_AUTH_PLAIN
    #define MAIL_USER                config->get_mailUsername().c_str()
    #define MAIL_PASS                config->get_mailPassword().c_str()
    #define MAIL_FROM                msg->get_sender().c_str()
    #define MAIL_FROM_NAME           "mail_handler"
    #define MAIL_SUBJECT             msg->get_subject().c_str()
    #define MAIL_BODY                msg->get_message().c_str()
    #define MAIL_TO                  msg->get_receiver().c_str()
    #define MAIL_TO_NAME             "target"
    struct smtp *smtp;
    int rc;
    rc = smtp_open( MAIL_SERVER, MAIL_PORT, MAIL_CONNECTION_SECURITY, (smtp_flag)MAIL_FLAGS, MAIL_CAFILE, &smtp);
    if ( rc==SMTP_STATUS_OK ) {
	rc |= smtp_auth(smtp, MAIL_AUTH, MAIL_USER, MAIL_PASS);
	if ( rc==SMTP_STATUS_OK ) {
	    rc |= smtp_address_add(smtp, SMTP_ADDRESS_FROM, MAIL_FROM, MAIL_FROM_NAME);
            rc |= smtp_address_add(smtp, SMTP_ADDRESS_TO, MAIL_TO, MAIL_TO_NAME);
            rc |= smtp_header_add(smtp, "Subject", MAIL_SUBJECT);
            rc |= smtp_header_add(smtp, "Content-Type", "text/plain"); 
            rc |= smtp_mail(smtp, MAIL_BODY);
        }
        rc |= smtp_close(smtp);
    }
    if ( rc!=SMTP_STATUS_OK ) {
        std::cout << "    MailHandler::Send Error: Server: " << MAIL_SERVER << "\n";
    }
}

void MailHandler::SendOne(SmtpMessage *msg) {
        if ( config->get_mailReceiver() != "" ) {
            std::cout << " msg Mail Receiver: " << msg->get_receiver() << "\n";
            msg->set_receiver(config->get_mailReceiver());
            std::cout << " conf Mail Receiver: " << config->get_mailReceiver() << "\n";
            std::cout << " msg Mail Receiver: " << msg->get_receiver() << "\n";
        }
        if ( config->get_mailSender() != "" )  msg->set_sender(config->get_mailSender());
        if ( config->get_mailSubject() != "" ) msg->set_subject(config->get_mailSubject());

        Send(msg);
}
