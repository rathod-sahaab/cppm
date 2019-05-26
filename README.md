# P-M : Portable Map family library

This library provides data stucture and file mechanism for parsing and writing [ Netpbm ](https://en.wikipedia.org/wiki/Netpbm_format) family images.
- PPM (Portable Pix Map)
- PGM (Portable Grey Map)
- PBM (Portable Bit Map)

## WARNING!
This format is highly inefficient, and shouldn't be used for serious purposes.

USAGE
---
This is a header only library and thus include it like any other in your project
```cpp
#include "ppm.hpp"
```
or path in include
```cpp
#include "./relative/path/ppm.hpp"
```

or use compilation flags(Recommended)
```
clang++ main.cpp -Irelative/path -o output_file
```

Library
---
Three classes are provided
- `PixBitMap` (Black or white)
- PixGreyMap (many shades of grey :D )
- PixPixMap (Rainbow(color) mode)

PixBitMap constructor takes two arguments width and height

PixGreyMap constructor takes three arguments width, height and max_value(`unsigned`)

PixPixMap constructor takes three arguments width, height and max_value(`RGB`)

`struct` RGB is included in the header and is just collection of varible doesnt imposes any bounds on value.Use the constructor RGB(red,green,blue) to create color objects see examples;


**Functions**
```cpp
fill(val)
```
This member function fills the image with passed argument

```
set_pixel(x,y,val)
```

This sets pixel with x and y co-ordinates to given val.

**Note** Use RGB values with PixPixMap.

**Note** For sequential access *i.e.* use row major access as it would benfit from CPU caching.
```cpp
for(unsigned y = 0; y < p.get_height(); ++y) {
	for(unsigned x = 0; x < p.get_width(); ++x) {
		p.set_pixel(x,y,val);
	}
}
```
and not
```cpp
for(unsigned x = 0; x < p.get_width(); ++x) {
	for(unsigned y = 0; y < p.get_height(); ++y) {
		p.set_pixel(x,y,val);
	}
}
```

**Output**
create a ofstream file with extention `.ppm` and use output operator
```cpp
std::ofstream image("name.ppm");
image << p;
image.close();
```
