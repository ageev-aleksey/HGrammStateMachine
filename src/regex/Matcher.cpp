//
// Created by nrx on 03.04.2020.
//

#include "regex/Graph.h"
#include "regex/Matcher.h"
#include "regex/util.h"

Matcher::Matcher(Graph<std::pair<bool, std::set<size_t>>, char> g) : fsm(g) {};

Matcher Matcher::compile(std::string regex) {
    std::string pn = util::convertToRPN(regex);
    Graph<Empty, char> nfsm = util::graphFromRegex(pn);
    Graph<std::pair<bool, std::set<size_t>>, char> dfsm = util::convertNFSMtoDFSM2(nfsm);
    Matcher m(util::minimizeDFSM(dfsm));
    return m;
}

Matcher::Matcher(Matcher &m) {
    *this = m;
}

Matcher& Matcher::operator=(Matcher &m) {
    fsm = m.fsm;
}

Matcher& Matcher::operator=(Matcher &&m) {
    fsm = m.fsm;
}

bool Matcher::match(std::string str) {
    auto state = fsm.begin();
    bool nextState;
    for(auto &el : str) {
        nextState = false;
        const std::list<Graph<std::pair<bool, std::set<size_t>>, char>::Link> &link = state.getLinks();
        for(auto itr = link.cbegin(); itr != link.cend(); ++itr){
            if(itr->data == el) {
                nextState = true;
                state = itr->node;
                break;
            }
        }
        if(!nextState) {
            return false;
        }

    }
    //isTerminalState
    return state.getData().first;
}
