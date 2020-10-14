#include <iostream>
#include <Magick++.h>
#include <filesystem>
#include <string>

void printUsage();
void resample(Magick::Image& img, int w, int h);
bool arrContains(const std::vector<std::string> &arr, std::string &item);

namespace fs = std::filesystem;

int main(int argc, char ** argv)
{
    const std::vector<std::string> acceptedExtensions = {".JPG", ".PNG", ".JPEG"};
    std::string writePath = "";
    int width = 0, height = 0, counter = 1;
    bool verbose = true;
    
    if(argc < 4) {
        printUsage();
        exit(0);
    }
    
    std::string path = argv[1];
    // check if path is directory and create thumbnails subdir if so, else exit
    if(!fs::is_directory(path)) {
        std::cout << "Not a directory: " << path << std::endl;
        printUsage();
        exit(0);
    } else {
        fs::create_directory(path+"/thumbnails");
        writePath = path + "/thumbnails";
    }
    
    try {
        width = atoi(argv[2]);
        height = atoi(argv[3]);
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
        printUsage();
        exit(1);
    }
    
    Magick::InitializeMagick(*argv);
    
    for (const auto & entry : fs::directory_iterator(path)){
        std::string filename = fs::path(entry.path().filename()).replace_extension();
        std::string ext = entry.path().extension();
        std::string writeTo = writePath + "/" + filename + "_thumbnail" + ext;
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c){ return std::toupper(c); });
        
        if(arrContains(acceptedExtensions, ext)) {
            try {
                if(verbose)
                    std::cout << "resampling file " << (counter++) << " - " << filename << ext << std::endl;
                
                Magick::Image image;
                image.read(entry.path());
                resample(image, width, height);
                image.write(writeTo);
            } catch( std::exception& e) {
                std::cout << e.what() << std::endl;
                printUsage();
                exit(1);
            }
        }
    }
    return 0;
}

void printUsage() {
    std::cout << "Usage: thumbCreate path-to-directory width height" << std::endl;
    std:: cout << "Bulk rescale images in directory to given width/height (preserves aspect ratio)" << std::endl;
}

void resample(Magick::Image& img, int w, int h) {
    img.sample( Magick::Geometry(w,h) );
}

bool arrContains(const std::vector<std::string> &arr, std::string &item) {
    return std::find(std::begin(arr), std::end(arr), item) != std::end(arr);
}
