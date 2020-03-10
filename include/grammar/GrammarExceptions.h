//
// Created by nrx on 05.03.2020.
//

#ifndef STATE_MACHINE_INCORRECTPRODUCTION_H
#define STATE_MACHINE_INCORRECTPRODUCTION_H
#include <stdexcept>
#include <string>

class IncorrectProduction : public std::logic_error {
public:
    IncorrectProduction(const std::string &msg);
};


class AlphabetError : public std::logic_error {
public:
    AlphabetError(const std::string &msg);
};

class BuildingException : public std::logic_error {
public:
    BuildingException(const std::string &msg);
};
#endif //STATE_MACHINE_INCORRECTPRODUCTION_H
