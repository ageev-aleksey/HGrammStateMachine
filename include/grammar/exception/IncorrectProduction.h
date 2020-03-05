//
// Created by nrx on 05.03.2020.
//

#ifndef STATE_MACHINE_INCORRECTPRODUCTION_H
#define STATE_MACHINE_INCORRECTPRODUCTION_H
#include <stdexcept>
#include <string>

class IncorrectProduction : public std::logic_error {
public:
    IncorrectProduction(std::string msg);
};

#endif //STATE_MACHINE_INCORRECTPRODUCTION_H
