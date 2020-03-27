//
// Created by nrx on 13.03.2020.
//

#ifndef STATE_MACHINE_MATRIX_H
#define STATE_MACHINE_MATRIX_H
#include <vector>
#include "grammar/definitions.h"

template<typename T>
class Matrix {
public:
    /**
     *
     * @param nrow число строк
     * @param ncol число столбцов
     */
    Matrix(size_t nrow, size_t ncol) {
        data.resize(nrow*ncol);
        this->nrow = nrow;
        this->ncol = ncol;
    }
    Matrix(const Matrix &m) {
        nrow = m.nrow;
        ncol = m.ncol;
        data = m.data;
    }
    /**
     * получение элемента матрицы по индексам
     * @param i индекс строки
     * @param j индекс столбца
     * @return
     */
    T& at(size_t i, size_t j) {
        return data[i*ncol+j];
    }
    const T& at(size_t i, size_t j) const {
        return data[i*ncol+j];
    }
    size_t getNcol() const{
        return ncol;
    }
    size_t getNrow() const{
        return nrow;
    }
private:
    std::vector<T> data;
    size_t ncol;
    size_t nrow;
};


#endif //STATE_MACHINE_MATRIX_H
