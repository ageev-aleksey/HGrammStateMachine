//
// Created by nrx on 05.03.2020.
//


#include "grammar/exception/IncorrectProduction.h"

IncorrectProduction::IncorrectProduction(std::string msg) : std::logic_error(msg){

}