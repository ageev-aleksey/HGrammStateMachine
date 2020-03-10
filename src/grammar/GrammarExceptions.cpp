//
// Created by nrx on 05.03.2020.
//


#include "grammar/GrammarExceptions.h"

IncorrectProduction::IncorrectProduction(const std::string &msg) : std::logic_error(msg){

}

AlphabetError::AlphabetError(const std::string &msg) : std::logic_error(msg) {

}

BuildingException::BuildingException(const std::string &msg) : std::logic_error(msg) {

}