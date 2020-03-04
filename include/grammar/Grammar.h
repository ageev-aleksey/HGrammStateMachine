
class Grammar {
    virtual bool inTerminal(const Symbol &s) = 0;
    virtual bool inNonTerminal(const Symbol &s) = 0;
};