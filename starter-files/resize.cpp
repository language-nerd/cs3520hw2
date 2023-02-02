#include <string>
#include "assert.h"
#include <iostream>
#include <fstream>
#include "Image_test_helpers.h"
#include "processing.cpp"

using std::string;
using std::ifstream;
using namespace std;

int main(int argc, char* argv[]) {
    // check to make sure there's the appropriate number of command line args (4 or 5)
    if(argc < 4) {
         cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 2; // returning 2 means there was an error in the program
    }

    string executable_name = argv[0];
    
    string input_file = argv[1];
    ifstream ifs_input (input_file);

    if(!ifs_input.is_open()) { // if the file could not be opened, print an error message
        cout << "Error opening file: " << input_file << endl;
        return 2; // returning 2 means there was an error in the program
    }
    const Image img = Image::read_ppm(ifs_input);
    Image carved_Img;

    string output_file = argv[2];

    
    
    if(argc > 4) { // there is 5 arguments; meaning there is a width AND height
    string width_str = argv[3];
    // converting width_str to a num
    int width = stoi(width_str);

    string height_str = argv[4]; 
    // converting height_str to a num
    int height = stoi(height_str);
    // checking for illegal width or height
    if(width < 0 || width > img.get_width() || height < 0 || height > img.get_height()) {
        cout << "Usage: resize.exe " << input_file << " " << output_file << " " << width_str << "[" << height_str << "]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 2; // returning 2 means there was an error in the program
    }
    // create the seam_carved image
    carved_Img = seam_carve(img, width, height);
    } else { // there is 4 arguments; user did not give height, only width
    string width_str = argv[3];
    // converting width_str to a num
    int width = stoi(width_str);
    // checking for illegal width
        if(width < 0 || width > img.get_width()) {
         cout << "Usage: resize.exe " << input_file << " " << output_file << " " << width_str << "[" << img.get_height() << "]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 2; // returning 2 means there was an error in the program
        }
    // create the seam_carved image
    carved_Img = seam_carve_width(img, width);

    }

    // printing to output_file the new seam_carved image
    ofstream ofs_output (output_file);
    if(!ofs_output.is_open()) { // if the output file could not be opened, print an error message
        cout << "Error opening file: " << output_file << endl;
        return 2; // returning 2 means there was an error in the program
    }

    carved_Img.print(ofs_output);
    // returning a non-zero value
    return 1; // returning 1 means the program worked successfully
    

}