#include "Matrix.hpp"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image::print produces the correct output.
TEST(test_print_basic) {
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image img(2, 2);
  img.set_pixel(0, 0, red);
  img.set_pixel(0, 1, green);
  img.set_pixel(1, 0, blue);
  img.set_pixel(1, 1, white);

  // Capture our output
  ostringstream actual;
  img.print(actual);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(correct.str(), actual.str());
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// Tests whether an image is read and made correctly
// according to the contents in a string stream
TEST(test_reading_img) {
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image img = Image::read_ppm(ss_input);
  ASSERT_EQUAL(img.get_width(), 2);
  ASSERT_EQUAL(img.get_height(), 2);

  Pixel p1 = {255, 0, 0};
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 0), p1));
  Pixel p2 = {0, 255, 0};
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 1), p2));
  Pixel p3 = {0, 0, 255};
  ASSERT_TRUE(Pixel_equal(img.get_pixel(1, 0), p3));
  Pixel p4 = {255, 255, 255};
  ASSERT_TRUE(Pixel_equal(img.get_pixel(1, 1), p4));

}

// Tests the image constructor for creating an empty image
// by checking if the width and height are equal to 0
TEST(test_create_empty_img) {
  Image img = Image();
  ASSERT_EQUAL(img.get_width(), 0);
  ASSERT_EQUAL(img.get_height(), 0);
}

// Tests the image constructor for creating a 4x3 image
// with all pixels initialized to 0 values by
// checking if the width and height were set appropriately 
// and if each pixel has a value of 0 for each red, green, and blue
// channel
TEST(test_create_img_with_zero_pixel_values) {
  Image img = Image(4, 3);
  ASSERT_EQUAL(img.get_width(), 4);
  ASSERT_EQUAL(img.get_height(), 3);
  Pixel p = {0, 0, 0};

  for(int h = 0; h < img.get_height(); ++h) {
    for(int w = 0; w < img.get_width(); ++w) {
      ASSERT_TRUE(Pixel_equal(img.get_pixel(h,w), p));
    }
  }
}

// Tests the image constructor fo creating a 5x3
// image with all the pixels initialized to a given pixel
// by checking if the width, height, and all the pixels were set appropriately
TEST(test_create_img_with_given_pixel_value) {
  const Pixel p = {255, 255, 255};
  Image img = Image(5, 3, p);
  ASSERT_EQUAL(img.get_width(), 5);
  ASSERT_EQUAL(img.get_height(), 3);
 

  for(int h = 0; h < img.get_height(); ++h) {
    for(int w = 0; w < img.get_width(); ++w) {
      ASSERT_TRUE(Pixel_equal(img.get_pixel(h,w), p));
    }
  }
}

// tests printing an empty image
TEST(test_print_empty_img) {

  Image img = Image();

  // Capture our output
  ostringstream actual;
  img.print(actual);

  // Correct output
  ostringstream correct;
  correct << "P3\n0 0\n255\n";
  ASSERT_EQUAL(correct.str(), actual.str());

}

// tests reading an empty image
TEST(read_empty_img) {
  string input = "P3 0 0\t255\n";
  std::istringstream ss_input(input);
  Image img = Image::read_ppm(ss_input);
  ASSERT_EQUAL(img.get_width(), 0);
  ASSERT_EQUAL(img.get_height(), 0);
}

// tests the get_pixel method by checking that the
// appropriate pixel was received
TEST(get_pixel) {
  const Pixel fill_val = {0, 0, 255};
  Image img = Image(4, 3, fill_val);

  ASSERT_TRUE(Pixel_equal(img.get_pixel(2, 3), fill_val));
  ASSERT_TRUE(Pixel_equal(img.get_pixel(1, 2), fill_val));

}

// tests the set_pixel method
// by checking if the pixel before was changed to
// the given pixel
TEST(set_pixel) {
  const Pixel fill_val = {0, 0, 255};
  Image img = Image(4, 3, fill_val);

  // check before setting
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 3), fill_val));
  const Pixel red = {255, 0, 0};
  img.set_pixel(0, 3, red);
  // check after setting
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 3), red));

  // check before setting
  ASSERT_TRUE(Pixel_equal(img.get_pixel(1, 3), fill_val));
  const Pixel green = {0, 255, 0};
  img.set_pixel(1, 3, green);
  // check after setting
  ASSERT_TRUE(Pixel_equal(img.get_pixel(1, 3), green));

  // check before setting
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 3), red));
  const Pixel white = {255, 255, 255};
  img.set_pixel(0, 3, white);
  // check after setting
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 3), white));
}



// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST_MAIN()
