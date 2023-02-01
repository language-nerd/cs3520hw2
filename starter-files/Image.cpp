#include <iostream>
#include <string>
#include "Image.hpp"
#include "assert.h"

using std::cout;
using std::string;
using std::endl;


  Image::Image(): m_width(0), m_height(0) {}

  Image::Image(int width, int height): m_width(width), m_height(height), 
  m_red_channel(width, height), m_green_channel(width, height), m_blue_channel(width, height){}

  Image::Image(int width, int height, const Pixel& fill): m_width(width), m_height(height),
    m_red_channel(width, height, fill.r), m_green_channel(width, height, fill.g), m_blue_channel(width, height, fill.b) {}

Image Image::read_ppm(std::istream& is) {
    // have an idea of how to do this but not sure how to skip some parts in the ppm file
    string token;
    is >> token;

    int width; // relates to columns
    is >> width;

    int height; // relates to rows
    is >> height;


    int intensity;
    is >> intensity; // intensity has a value of 255

    int red;
    int green;
    int blue;

    int row = 0;
    int col = 0;

    Image img = Image(width, height);
    while(is >> red && is >> green && is >> blue) {
        img.set_pixel(row, col, Pixel{red, green, blue});
        if(col < width) {
            ++col;
        }
        if(col == width) {
            if(row < height) {
                ++row;
            }
            col = 0;
        } 
    }
    return img;
}

void Image::print(std::ostream& os) const {
    os << "P3" << endl;
    os << m_width << " " << m_height << endl;
    os << c_max_intensity << endl;
    for(int h = 0; h < m_height; ++h) { // h refers to the current row 
        for(int w = 0; w < m_width; ++w) { // w refers to the current col
            os << m_red_channel.at(h, w) << " " << m_green_channel.at(h, w) << " " << m_blue_channel.at(h, w) << " ";
        }
        os << "\n"; // print a new line after printing out a whole row
    }
}

int Image::get_width() const {
    return m_width;
}

int Image::get_height() const {
    return m_height;
}

Pixel Image::get_pixel(int row, int column) const {
    assert(row >= 0 && row < m_height && column >= 0 && column < m_width);
    return Pixel{m_red_channel.at(row, column), m_green_channel.at(row, column), m_blue_channel.at(row, column)};
}

void Image::set_pixel(int row, int column, const Pixel& color) {
    assert(row >= 0 && row < m_height && column >= 0 && column < m_width);
    m_red_channel.at(row, column) = color.r;
    m_green_channel.at(row, column) = color.g;
    m_blue_channel.at(row, column) = color.b;
}