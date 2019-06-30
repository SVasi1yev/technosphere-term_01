#include <cstring>
#include <vector>
#include <stdexcept>

class Matrix {
    class Row {
        size_t size;
        std::vector<int> row;
        
    public:
        Row(size_t size): size(size) {
            row = std::vector<int>(size, 0);
        }

        size_t getSize () const { return size; }

        Row operator*= (int num) {
            for (size_t i = 0; i < size; i++) {
                row[i] *= num;
            }
            return *this;
        }

        const int& operator[] (size_t i) const {
            if (i >= size) {
                throw std::out_of_range("");
            }
            return row[i];
        }

        int& operator[] (size_t i) {
            if (i >= size) {
                throw std::out_of_range("");
            }
            return row[i];
        }
        
        bool operator== (const Row& other) const {
            if (this == &other) {
                return true;
            }

            if (size != other.getSize()) {
                return false;
            }

            for (size_t i = 0; i < size; i++) {
                if (row[i] != other[i]) {
                    return false;
                }
            }

            return true;
        }

        bool operator!= (const Row& other) const {
            return !(*this == other);
        }
    };

    size_t rows_num;
    size_t cols_num;
    std::vector<Row> rows;
    
public:
    Matrix (size_t rows_num, size_t cols_num)
        : rows_num(rows_num), cols_num(cols_num) {
        rows = std::vector<Row>(rows_num, Row(cols_num));
    }

    size_t getRows () const { return rows_num; }
    size_t getColumns () const { return cols_num; }

    Matrix operator*= (int num) {
        for (size_t i = 0; i < rows_num; i++) {
            rows[i] *= num;
        }
        return *this;
    }

    const Row& operator[] (size_t i) const {
        if (i >= rows_num) {
            throw std::out_of_range("");
        }
        return rows[i];
    }

    Row& operator[] (size_t i) {
        if (i >= rows_num) {
            throw std::out_of_range("");
        }
        return rows[i];
    }
    
    bool operator== (const Matrix& other) const {
        if (this == &other) {
            return true;
        }

        if (rows_num != other.getRows()
        || cols_num != other.getColumns()) {
            return false;
        }

        for (size_t i = 0; i < rows_num; i++) {
            if (rows[i] != other[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!= (const Matrix& other) const {
        return !(*this == other);
    }
};