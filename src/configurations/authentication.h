/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_CONFIGURATIONS_AUTHENTICATION_H
#define MAILBRIDGE_CONFIGURATIONS_AUTHENTICATION_H

#include <string>
#include <utility>

/**
 * Authentication credentials.
 */
class Authentication {
private:
    std::string password;
    std::string username;
public:
    /**
     * Authentication constructor.
     */
    Authentication(std::string username, std::string password) :
            password(std::move(password)), username(std::move(username)) {};

    /**
     * Authentication destructor.
     */
    ~Authentication() = default;

    /**
     * Gets the username.
     *
     * @return the username
     */
    std::string get_username() {
        return this->username;
    }

    bool operator==(const Authentication &other) const {
        return this->username == other.username && this->password == other.password;
    }

    /**
     * Verifies the compared password matches the stored password.
     *
     * @param compare the password to compare to
     * @return true if the passwords matches
     */
    bool password_matches(const std::string &compare) {
        return this->password == compare;
    }
};

#endif /* MAILBRIDGE_CONFIGURATIONS_AUTHENTICATION_H */