#include "processing.hpp"

namespace {
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2);
}

// Implement the functions declared in processing.hpp here.
Image rotate_left(const Image& img) {

}
Image rotate_right(const Image& img) {

}
Matrix compute_energy_matrix(const Image& img) {

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
