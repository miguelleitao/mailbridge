/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_MESSAGES_SMTP_MESSAGE_H
#define MAILBRIDGE_MESSAGES_SMTP_MESSAGE_H

#include <string>

/**
 * An smtp message.
 */
class SmtpMessage {
    private:
        std::string message;
        std::string receiver;
        std::string sender;
        std::string subject;
    public:
        /**
         * SmtpMessage constructor.
         */
        SmtpMessage() : message(""), receiver(""), sender(""), subject("") {};

        /**
         * SmtpMessage destructor.
         */
        ~SmtpMessage() = default;

        /**
         * Gets the message of the email.
         *
         * @return the message
         */
        std::string get_message() {
            return this->message;
        }

        /**
         * Gets the receiver of the email.
         *
         * @return the receiver
         */
        std::string get_receiver() {
            return this->receiver;
        }

        /**
         * Gets the sender of the email.
         *
         * @return the sender
         */
        std::string get_sender() {
            return this->sender;
        }

        /**
         * Gets the subject of the email.
         *
         * @return the subject
         */
        std::string get_subject() {
            return this->subject;
        }

        /**
         * Sets the message of the email.
         *
         * @param msg the message
         */
        void set_message(std::string msg) {
            this->message = std::move(msg);
        }

        /**
         * Sets receiver of the email.
         *
         * @param recv the receiver
         */
         void set_receiver(std::string recv) {
             this->receiver = std::move(recv);
         }

        /**
         * Sets sender of the email.
         *
         * @param s the sender
         */
         void set_sender(std::string s) {
            this->sender = std::move(s);
         }

        /**
         * Sets the subject of the email.
         *
         * @param sub the subject
         */
        void set_subject(std::string sub) {
            this->subject = std::move(sub);
        }
};

#endif /* MAILBRIDGE_MESSAGES_SMTP_MESSAGE_H */
