#include <iostream>
#include "Matrix.hpp"

// using namespace std; // Are we supposed to have this here?
//hello we were just working on this -salute-


Matrix::Matrix(): m_width(0), m_height(0) {}

Matrix::Matrix(int width, int height): m_width(width), m_height(height) {
    for(int i = 0; i < width * height; ++i) {
        m_data.push_back(0);
    }
}

Matrix::Matrix(int width, int height, int fill_value): m_width(width), m_height(height){
    for(int i = 0; i < width * height; ++i) {
        m_data.push_back(fill_value);
    }
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

Matrix::Slice Matrix::get_row_slice(int row, int col_start, int col_end) const{
    std::vector<int> portion;
    // If col_start is less than zero, the first element of the returned slice
    // will be the first element of the row.
    if(col_start < 0) {
        col_start = 0;
    }
    // If col_end is greater than the width of this Matrix, the last element of
    // the returned slice will be the last element of the row.
    if(col_end > m_width) {
        col_end = m_width;
    }
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

