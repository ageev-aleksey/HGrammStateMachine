//
// Created by nrx on 03.04.2020.
//

#ifndef STATE_MACHINE_MATCHER_H
#define STATE_MACHINE_MATCHER_H
#include <set>
#include "regex/Graph.h"

class Matcher {
public:
    bool match(std::string str);
    static Matcher compile(std::string regex);
private:
    Matcher();
    Graph<std::pair<bool, std::set<size_t>>, char> fsm;

};


#endif //STATE_MACHINE_MATCHER_H
