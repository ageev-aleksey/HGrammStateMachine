//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_SYMBOL_H
#define STATE_MACHINE_SYMBOL_H
#include <cstddef>
#include <ostream>

class Symbol {
public:
    Symbol(char s);
    Symbol(const Symbol &s);
    Symbol& operator=(const Symbol &s);
    bool operator==(const Symbol &s) const;
    char toChar() const;

    friend class std::hash<Symbol>;
    friend std::ostream& operator<< (std::ostream &out, const Symbol &point);
private:
    char symbol;
};

namespace std {
    template<>
    struct hash<Symbol> {
        using result_ype = size_t;
        using argument_type = Symbol;

        size_t operator() (const Symbol &s) {
            return (size_t ) s.symbol;
        }
    };
}
std::ostream& operator<< (std::ostream &out, const Symbol &s);

#endif //STATE_MACHINE_SYMBOL_H