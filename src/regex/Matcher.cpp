//
// Created by nrx on 03.04.2020.
//

#include "regex/Graph.h"
#include "regex/Matcher.h"
#include "regex/util.h"

Matcher::Matcher() = default;

Matcher Matcher::compile(std::string regex) {
    std::string pn = util::convertToRPN(regex);
    Graph<Empty, char> nfsm = util::graphFromRegex(pn);
    Graph<std::pair<bool, std::set<size_t>>, char> dfsm = util::convertNFSMtoDFSM2(nfsm);
    Matcher m;
    m.fsm = util::minimizeDFSM(dfsm);
    return m;
}

bool Matcher::match(std::string str) {
    auto state = fsm.begin();
    bool nextState;
    for(auto &el : str) {
        nextState = false;
        const std::list<Graph<std::pair<bool, std::set<size_t>>, char>::Link> &link = state.getLinks();
        std::cout << link.size() << std::endl;
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
    return true;
}
