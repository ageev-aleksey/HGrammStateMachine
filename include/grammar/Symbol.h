//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_SYMBOL_H
#define STATE_MACHINE_SYMBOL_H
#include <cstddef>
#include <ostream>

class Symbol {
public:
    static constexpr char EMPTY_SYMBOL = '@';
    static constexpr char ONE_SYMBOL = 'e';
    Symbol();
    Symbol(char s);
    void set(char s);
    Symbol(const Symbol &s);
    Symbol& operator=(const Symbol &s);
    char toChar() const;
    bool isEmptySymbol() const;
    bool isOneSymbol() const;

     bool operator<(const Symbol &other) const;
     bool operator==(const Symbol &other) const;
    bool operator!=(const Symbol &other) const;

    friend class std::hash<Symbol>;
    friend std::ostream& operator<< (std::ostream &out, const Symbol &point);
private:
    char symbol;
};


namespace std {
    template <>
    class hash<Symbol> {
    public:
        size_t operator()(const Symbol &s) const
        {
            return (size_t) s.symbol;
        }
    };

    template<>
    class equal_to<Symbol> {
    public:
        bool operator() (const Symbol &left, const Symbol &right) const {
            return left == right;
        }
    };
}

std::ostream& operator<< (std::ostream &out, const Symbol &s);

#endif //STATE_MACHINE_SYMBOL_H
