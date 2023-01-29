#include "Matrix.hpp"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

// Here's a free test for you! Model yours after this one.
// Add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix::at returns that value for each element.
TEST(test_Matrix_fill_basic)
{
  const int width = 3;
  const int height = 5;
  const int value = 42;
  auto mat = Matrix(width, height, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(mat.at(r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

// Fills a 2x2 Matrix using the constructor that only takes in a width and height
// and each cell in the matrix is initialized to 0.
TEST(test_Matrix_fill_with_zeros) {
  const int width = 2;
  const int height = 2;
  auto mat = Matrix(width, height);

  ASSERT_EQUAL(mat.get_height(), 2);
  ASSERT_EQUAL(mat.get_width(), 2);
  ASSERT_EQUAL(mat.get_height(), mat.get_width());
  
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(mat.at(r, c), 0);
    }
  }
}

// Creates an Matrix with the constructor that creates an empty one
TEST(test_Matrix_empty) {
  auto mat = Matrix();
  ASSERT_EQUAL(mat.get_height(), 0);
  ASSERT_EQUAL(mat.get_width(), 0);
  ASSERT_EQUAL(mat.get_height(), mat.get_width());
}

// tests getting values from cells in a Matrix filled with different numbers
TEST(text_Matrix_fill_different_nums) {
  int width = 5;
  int height = 3;
  auto mat = Matrix(width, height);
  mat.at(0, 0) = 1;
  mat.at(0, 1) = 3;
  mat.at(0, 2) = 7;
  mat.at(0, 3) = 1;
  mat.at(0, 4) = 3;
  mat.at(1, 0) = 1;
  mat.at(1, 1) = 4;
  //mat.at(1, 2) = 1; already set at 0
  mat.at(1, 3) = 13;
  mat.at(1, 4) = 4;
  mat.at(2, 0) = 3;
  mat.at(2, 1) = -6;
  mat.at(2, 2) = 2;
  mat.at(2, 3) = 10;
  //mat.at(2, 4) = 1; already set at 0

  ASSERT_EQUAL(mat.at(0, 0), 1);
  ASSERT_EQUAL(mat.at(1, 3), 13);
  ASSERT_EQUAL(mat.at(2, 1), -6);
  ASSERT_EQUAL(mat.at(2, 4), 0);

}

TEST(test_Matrix_row_slice_norm) {
    int width = 5;
  int height = 3;
  auto mat = Matrix(width, height);
  mat.at(0, 0) = 1;
  mat.at(0, 1) = 3;
  mat.at(0, 2) = 7;
  mat.at(0, 3) = 1;
  mat.at(0, 4) = 3;
  mat.at(1, 0) = 1;
  mat.at(1, 1) = 4;
  //mat.at(1, 2) = 1; already set at 0
  mat.at(1, 3) = 13;
  mat.at(1, 4) = 4;
  mat.at(2, 0) = 3;
  mat.at(2, 1) = -6;
  mat.at(2, 2) = 2;
  mat.at(2, 3) = 10;
  //mat.at(2, 4) = 1; already set at 0

  std::vector<int> portion = mat.get_row_slice(0, 1, 3).data;
  ASSERT_EQUAL(portion.at(0), 3);
  ASSERT_EQUAL(portion.at(1), 7);
  ASSERT_EQUAL(portion.size(), 2);
}

TEST(test_Matrix_row_slice_col_start_less_than_zero) {
  int width = 5;
  int height = 3;
  auto mat = Matrix(width, height);
  mat.at(0, 0) = 1;
  mat.at(0, 1) = 3;
  mat.at(0, 2) = 7;
  mat.at(0, 3) = 1;
  mat.at(0, 4) = 3;
  mat.at(1, 0) = 1;
  mat.at(1, 1) = 4;
  //mat.at(1, 2) = 1; already set at 0
  mat.at(1, 3) = 13;
  mat.at(1, 4) = 4;
  mat.at(2, 0) = 3;
  mat.at(2, 1) = -6;
  mat.at(2, 2) = 2;
  mat.at(2, 3) = 10;
  //mat.at(2, 4) = 1; already set at 0

  std::vector<int> portion = mat.get_row_slice(0, -1, 3).data;
  ASSERT_EQUAL(portion.at(0), 1);
  ASSERT_EQUAL(portion.at(1), 3);
  ASSERT_EQUAL(portion.at(2), 7);
  ASSERT_EQUAL(portion.size(), 3);
}

TEST(test_Matrix_row_slice_col_end_greater_than_width) {
  int width = 5;
  int height = 3;
  auto mat = Matrix(width, height);
  mat.at(0, 0) = 1;
  mat.at(0, 1) = 3;
  mat.at(0, 2) = 7;
  mat.at(0, 3) = 1;
  mat.at(0, 4) = 3;
  mat.at(1, 0) = 1;
  mat.at(1, 1) = 4;
  //mat.at(1, 2) = 1; already set at 0
  mat.at(1, 3) = 13;
  mat.at(1, 4) = 4;
  mat.at(2, 0) = 3;
  mat.at(2, 1) = -6;
  mat.at(2, 2) = 2;
  mat.at(2, 3) = 10;
  //mat.at(2, 4) = 1; already set at 0

  std::vector<int> portion = mat.get_row_slice(2, 0, 7).data;
  ASSERT_EQUAL(portion.at(0), 3);
  ASSERT_EQUAL(portion.at(1), -6);
  ASSERT_EQUAL(portion.at(2), 2);
  ASSERT_EQUAL(portion.at(3), 10);
  ASSERT_EQUAL(portion.at(4), 0);
  ASSERT_EQUAL(portion.size(), 5);
}

// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST_MAIN()
