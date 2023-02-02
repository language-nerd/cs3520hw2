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

  return energy_matrix;
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

  return cost_matrix;
}
std::vector<int> find_minimal_vertical_seam(const Matrix& cost) {
  vector<int> seam(cost.get_height());

  int minimum_cost_pixel = 0; // default to leftmost pixel
  int minimum_cost = cost.at(minimum_cost_pixel, cost.get_height()-1); // default to the cost of the bottom left pixel

  for (int i = 0; i < cost.get_width(); ++i){
    if (cost.at(i, cost.get_height()-1) < minimum_cost){ // if cost is less than the minimum_cost defined by the leftmost pixel
      minimum_cost_pixel = i; // save the pixel x coordinate
      minimum_cost = cost.at(i, cost.get_height()-1); // save the minimum cost to check against others in the row
    }
  }

  for (int j = cost.get_width()-1; j >= 0; --j){
    if(j = cost.get_width()-1){ // if bottom row
      seam.at(cost.get_height()-1) = minimum_cost_pixel; // set the seam value to the current minimum cost pixel
    }
    else { // if any row above the bottom row, check itself and neighbors for lowest
      int left_pixel = minimum_cost_pixel - 1;
      int right_pixel = minimum_cost_pixel + 1;

      int lowest_cost = cost.at(minimum_cost_pixel, j);
      int current_lowest = 0; // -1 is left, 0 is current, 1 is right

      if (left_pixel >= 0){ // if left bound is valid
        int left_cost = cost.at(minimum_cost_pixel-1, j);
        if (left_cost <= lowest_cost) {
          lowest_cost = left_cost;
          current_lowest = -1;
        }
      }
      if (right_pixel <= cost.get_width()-1){ // if right bound is valid
        int right_cost = cost.at(minimum_cost_pixel+1, j);
        if (right_cost < lowest_cost) {
          lowest_cost = right_cost;
          current_lowest = 1;
        }
      }

      minimum_cost_pixel += current_lowest;
      seam.at(cost.get_height()-1) = minimum_cost_pixel; // set the seam value to the current minimum cost pixel
    }
  }

  return seam;
}

Image remove_vertical_seam(const Image& img, const std::vector<int>& seam) {
  Image trimmed_image = Image(img.get_width()-1, img.get_height());

  for (int k = 0; k < seam.size(); ++k){ // for each in seam (represents a row)
    for (int l = 0; l < seam.at(k)){
      trimmed_image.set_pixel(l, k, img.get_pixel(l, k));
    }
    if (seam.at(k) < img.get_width()-1){
      for (int m = seam.at(k)+1; m < img.get_width(); ++k){
        trimmed_image.set_pixel(l + seam.at(k), k, img.get_pixel(l, k));
      }
    }
  }
}

Image seam_carve_width(const Image& img, int new_width) {
  Image finished_image;
  while(img.get_width > new_width){
    finished_image = remove_vertical_seam(img, find_minimal_vertical_seam(compute_vertical_cost_matrix(img)));
  }
  return finished_image;
}

Image seam_carve_height(const Image& img, int new_height) {
  Image finished_image = rotate_left(img);
  finished_image = seam_carve_width(finished_image);
  finished_image = rotate_right(finished_image);
  return finished_image;
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
