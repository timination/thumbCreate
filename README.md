# thumbCreate

thumbCreate is a simple C++ command line tool that uses ImageMagick for taking a directory of images and rescaling them to a given width or height to generate thumbnails. Original images are not overwritten.

## Installation

- Download/Clone [ImageMagick](https://github.com/ImageMagick) source
- extract and navigate to the root directory of extracted files
- run `./configure CXX=g++ CXXFLAGS=-O2`
- run `make`
- run `make install`
- Download/Clone `thumbCreate.cpp`
- compile with: 
```terminal
g++ -O2 thumbCreate.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs` -std=c++17 -o thumbCreate.out
```

## Usage

```terminal
- run with: ./thumbCreate.out /path/to/images width height
- Example: ./thumbCreate.out /Users/timination/photos 200 200
```
**note:** a `thumbnails` directory is created within the given path, it does not check if this already exists and images inside of `thumbnails` with matching output filenames will be overwritten. 
E.g. if I rescale `image_x.jpg`, it will create `/thumbnails/image_x_thumbnail.jpg` which may be overwritten by another `image_x_thumbnail.jpg`.

## Contributing
Pull requests are welcome. 

## License
[MIT](https://choosealicense.com/licenses/mit/)
