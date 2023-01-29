#include <iostream>
#include <string>
#include "Image.hpp"

using std::cout;
using std::string;
using std::endl;

  Image::Image(): m_width(0), m_height(0) {}

  Image::Image(int width, int height): m_width(width), m_height(height){
    for(int h = 0; h < height; ++h) {
        for(int w = 0; w < width; ++w) {
            m_red_channel.at(h, w) = 0;
            m_green_channel.at(h, w) = 0;
            m_blue_channel.at(h, w) = 0;
        }
    }
  }

  Image::Image(int width, int height, const Pixel& fill): m_width(width), m_height(height) {
    for(int h = 0; h < height; ++h) { // height relates to the rows (y values)
        for(int w = 0; w < width; ++w) { // width relates to the columns (x values)
            m_red_channel.at(h, w) = fill.r;
            m_green_channel.at(h, w) = fill.g;
            m_blue_channel.at(h, w) = fill.b;
        }
    }
  }

Image Image::read_ppm(std::istream& is) {
    // have an idea of how to do this but not sure how to skip some parts in the ppm file
    string token;
    is >> token;
    if(token.compare("P3")) {
        cout << "This is a valid ppm file!" << "\n";
    }
    

    int width; // relates to columns
    is >> width;
    int height; // relates to rows
    is >> height;

    //getline(is, width);
    //getline(is, height);

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
        ++col;
        if(col == width) {
            ++row;
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
    return Pixel{m_red_channel.at(row, column), m_green_channel.at(row, column), m_blue_channel.at(row, column)};
}

void Image::set_pixel(int row, int column, const Pixel& color) {
    m_red_channel.at(row, column) = color.r;
    m_green_channel.at(row, column) = color.g;
    m_blue_channel.at(row, column) = color.b;
}