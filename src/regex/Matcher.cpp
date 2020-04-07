//
// Created by nrx on 03.04.2020.
//

#include "regex/Graph.h"
#include "regex/Matcher.h"
#include "regex/util.h"
#include "bprinter/table_printer.h"

Matcher::Matcher(Graph<std::pair<bool, std::set<size_t>>, char> g) : fsm(g) {};

Matcher Matcher::compile(std::string regex, std::ostream &fileNfsm, std::ostream &fileDfsm, std::ostream &fileMinDfm) {
    bprinter::TablePrinter tp(&std::cout);
    std::string pn = util::convertToRPN(regex);
    std::cout << "regex to rpn: " << pn << std::endl;
    Graph<Empty, char> nfsm = util::graphFromRegex(pn);
    auto t1 = util::buildConversionTable()
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
