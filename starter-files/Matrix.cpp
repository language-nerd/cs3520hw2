#include <iostream>
#include "Matrix.hpp"

// using namespace std; // Are we supposed to have this here?

int main() {

}

int Matrix::get_width() const {
    return m_width;
}

int Matrix::get_height() const {
    return m_height;
}

int& Matrix::at(int row, int column) {
    return m_data.at(column + m_width * row); 
}

const int& Matrix::at(int row, int column) const {
    return m_data.at(column + m_width * row); 
}

Matrix::Slice Matrix::get_row_slice(int row, int col_start, int col_end) {
    std::vector<int> portion;
    for(int i = col_start; i < col_end; ++i){
        portion.push_back(this->at(row, i)); //is this allowed?
    }
    Slice row_slice = {portion, row, col_start, col_end};
    return row_slice;
}

void Matrix::print(std::ostream& os) const {
 os << m_width << " " << m_height << "\n";
 for(int row = 0; row < m_height; ++row) {
    for(int col = 0; col < m_width; ++col) {
        os << this->at(row, col) << " ";
    }
    os << "\n";
 }
 
}

