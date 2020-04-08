//
// Created by nrx on 03.04.2020.
//

#include "regex/Graph.h"
#include "regex/Matcher.h"
#include "regex/util.h"

Matcher::Matcher(Graph<std::pair<bool, std::set<size_t>>, char> g) : fsm(g) {};

Matcher Matcher::compile(std::string regex, std::ostream &fileNfsm, std::ostream &fileDfsm, std::ostream &fileMinDfm) {
    std::string pn = util::convertToRPN(regex);
    std::cout << "regex to rpn: " << pn << std::endl;
    Graph<Empty, char> nfsm = util::graphFromRegex(pn);
    fileNfsm << util::graphToDOT(nfsm);
    Graph<std::pair<bool, std::set<size_t>>, char> dfsm = util::convertNFSMtoDFSM2(nfsm);
    fileDfsm << util::graphToDOT(dfsm);
    auto minDFM = util::minimizeDFSM(dfsm);
    fileMinDfm << util::graphToDOT(minDFM);
    Matcher m(minDFM);
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
    for(auto itrS = str.begin(); itrS != str.end(); ++itrS){
        char &el = *itrS;
        nextState = false;
        const std::list<Graph<std::pair<bool, std::set<size_t>>, char>::Link> &link = state.getLinks();
        //Печать конфигурации
        std::cout << "(" << state.getIndex() << "; ";
        for(auto tail = itrS; tail != str.end(); tail++) {
            std::cout << *tail;
        }
        std::cout << ")" << std::endl;

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
