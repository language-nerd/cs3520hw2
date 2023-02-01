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
  Matrix energy_matrix = Matrix(img.get_width(), img.get_height());
  int maximum_energy = 0;

  for (int i = 1; i < img.get_width()-1; ++i){
    for (int j = 1; j < img.get_height()-1; ++j){
      int position_energy = squared_difference(img.get_pixel(i, j-1), img.get_pixel(i, j+1)) + squared_difference(img.get_pixel(i-1, j), img.get_pixel(i+1, j));
      if (position_energy > maximum_energy){
        maximum_energy = position_energy;
      }
      energy_matrix.at(i, j) = position_energy;
    }
  }

  for (int i = 0; i < img.get_width(); ++i){
    for (int j = 0; j < img.get_height(); ++j){
      if (i == 0 || j == 0 || i == img.get_width-1 || j == img.get_height-1){
        energy_matrix.at(i, j) = maximum_energy;
      }
    }
  }
}

Matrix compute_vertical_cost_matrix(const Image& img) {
  Matrix cost_matrix = compute_energy_matrix(img);

  for (int j = 1; j < cost_matrix.get_height(); ++j){
    for (int i = 0; i < cost_matrix.get_width(); ++i){
      if (i == 0) { // if left edge
        int cost = cost_matrix.at(i, j); // start by initializing cost to the energy of the current pixel
        cost += min(cost_matrix.at(i, j-1), cost_matrix.at(i+1, j-1)); // add the min of the energy of the top and right
        cost_matrix.at(i,j) = cost; // set the computed cost
      }
      else if (i == cost_matrix.get_width()-1) { // if right edge
        int cost = cost_matrix.at(i, j); // start by initializing cost to the energy of the current pixel
        cost += min(cost_matrix.at(i, j-1), cost_matrix.at(i-1, j-1)); // add the min of the energy of the top and left
        cost_matrix.at(i,j) = cost; // set the computed cost
      }
      else {
        int cost = cost_matrix.at(i, j); // start by initializing cost to the energy of the current pixel
        cost += min(cost_matrix.at(cost_matrix.at(i-1, j-1), i, j-1), cost_matrix.at(i+1, j-1)); // add the min of the energy of the top, left, and right
        cost_matrix.at(i,j) = cost; // set the computed cost
      }
    }
  }
  
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
