/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_HANDLERS_HANDLER_H
#define MAILBRIDGE_HANDLERS_HANDLER_H


#include "../messages/smtp_message.h"

/**
 * Handles received incoming emails.
 */
class Handler {
public:
    /**
     * Handler constructor.
     */
    Handler() = default;

    /**
     * Handler destructor.
     */
    virtual ~Handler() = default;

    /**
     * Handles the message.
     *
     * @param message the message to handle
     */
    virtual void handle(SmtpMessage *message) = 0;
};

#endif /* MAILBRIDGE_HANDLERS_HANDLER_H */
