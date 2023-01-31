#include "processing.hpp"

namespace {
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2);
}

// Implement the functions declared in processing.hpp here.
Image rotate_left(const Image& img) {
  // Make a new image with inverted dimensions
  Image rotated_image = Image(img.get_height(), img.get_width());

  // Iterate through the image 
  for (int i = 0; i < img.get_width(); ++i){
    for (int j = 0; j < img.get_height(); ++j){
      Pixel scraped_pixel = img.get_pixel(i, j);
      rotated_image.set_pixel(j, img.get_width()-1-i, scraped_pixel);
    }
  }

  return rotated_image;
}
Image rotate_right(const Image& img) {
  // Make a new image with inverted dimensions
  Image rotated_image = Image(img.get_height(), img.get_width());

  // Iterate through the image 
  for (int i = 0; i < img.get_width(); ++i){
    for (int j = 0; j < img.get_height(); ++j){
      Pixel scraped_pixel = img.get_pixel(i, j);
      rotated_image.set_pixel(img.get_height()-1-j, i, scraped_pixel);
    }
  }
  
  return rotated_image;
}
Matrix compute_energy_matrix(const Image& img) {
  Matrix energy = Matrix(img.get_width(), img.get_height());

  for (int i = 0; i < img.get_width(); ++i){
    for (int j = 0; j < img.get_height(); ++j){
      int pixel_energy = 0;
      //int pixel_energy = squared_difference(p1, Pixel p2) + squared_difference(Pixel p1, Pixel p2);
      energy.at(i, j) = pixel_energy;
    }
  }

}
Matrix compute_vertical_cost_matrix(const Image& img) {

}
std::vector<int> find_minimal_vertical_seam(const Matrix& cost) {

}

Image remove_vertical_seam(const Image& img, const std::vector<int>& seam) {

}

Image seam_carve_width(const Image& img, int new_width) {

}

Image seam_carve_height(const Image& img, int new_height) {

}

Image seam_carve(const Image& img, int newWidth, int newHeight) {

}

namespace {
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2) {
    int dr = p2.r - p1.r;
    int dg = p2.g - p1.g;
    int db = p2.b - p1.b;
    // Divide by 100 is to avoid possible overflows
    // later on in the algorithm.
    return (dr*dr + dg*dg + db*db) / 100;
  }
}
