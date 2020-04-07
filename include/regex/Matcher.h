//
// Created by nrx on 03.04.2020.
//

#ifndef STATE_MACHINE_MATCHER_H
#define STATE_MACHINE_MATCHER_H
#include <set>
#include "regex/Graph.h"
#include <ostream>

class Matcher {
public:
    Matcher(Matcher &m);
    Matcher &operator=(Matcher &m);
    Matcher &operator=(Matcher &&m);

    bool match(std::string str);
    static Matcher compile(std::string regex, std::ostream &fileNfsm,  std::ostream &fileDfsm, std::ostream &fileMinDfm);

private:
    Matcher(Graph<std::pair<bool, std::set<size_t>>, char> g);
    Graph<std::pair<bool, std::set<size_t>>, char> fsm;

};


#endif //STATE_MACHINE_MATCHER_H
