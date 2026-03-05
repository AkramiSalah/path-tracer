#include <iostream>
#include <fstream>

constexpr int DEFAULT_IMAGE_SIZE = 256;
constexpr int MAX_COLOR = 255;

int main(int argc, char** argv){
    if (argc < 2 || argc > 4){
        std::cerr << "Usage Options: \n";
        std::cerr << "Option 1: hello_world <out_file_name> \n";
        std::cerr << "  Note: this will output a 256 x 256 image\n";
        std::cerr << "Option 2: hello_world <out_file_name> [size]\n";
        std::cerr << "  Note: this will output an image of size x size\n";
        std::cerr << "Option 3: hello_world <out_file_name> [width] [height]\n";
        std::cerr << "  Note: this will output an image of width x height\n";
        return 1;
    }

    int image_width = (argc >= 3) ? std::stoi(argv[2]) : DEFAULT_IMAGE_SIZE;
    int image_height = (argc >= 4) ? std::stoi(argv[3]) : image_width;
    std::ofstream image(argv[1]);
    if (!image) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }

    image << "P3" << '\n';
    image << image_width << ' ' << image_height
          << '\n';
    image << MAX_COLOR << '\n';

    for(int y = 0; y < image_height; y++){
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
        for(int x = 0; x < image_width; x++){
            auto r = double(x) / (image_width - 1);
            auto g = double(y) / (image_height - 1);
            auto b = 0.0;

            int ir = int(MAX_COLOR * r);
            int ig = int(MAX_COLOR * g);
            int ib = int(MAX_COLOR * b);
            
            image << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\r Done.                \n";
}