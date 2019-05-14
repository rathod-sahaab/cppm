#ifndef PM_HPP
#define PM_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Header {
  std::string format;
  unsigned width, height;
  unsigned max_pixel_value;

  friend std::ostream& operator<<(std::ostream&, const Header&);
};

template <class T>
class PixMap {
  Header head;
  std::vector<T> data;
  unsigned counter;

 public:
  PixMap();
  PixMap(std::string, unsigned width, unsigned height, unsigned max_value);
  /* ~PixMap(); */

  template <class U>
  friend std::ostream& operator<<(std::ostream&, const PixMap<U>&);

  PixMap<T>& operator<<(T);

  void set_format();
  void set_width();
  void set_height();
  void set_max();

  PixMap<T>& set_pixel(unsigned x, unsigned y, T val);
};
class PixBitMap : public PixMap<unsigned> {
 public:
  PixBitMap();
  PixBitMap(unsigned width, unsigned height);
  /* PixBitMap(unsigned, unsigned, std::string); */
};

class PixGreyMap : public PixMap<unsigned> {
 public:
  PixGreyMap();
  PixGreyMap(unsigned width, unsigned height, unsigned max_pixel_value);
};

struct RGB {
  unsigned r, g, b;
  friend std::ostream& operator<<(std::ostream&, const RGB&);
  RGB();
  RGB(unsigned, unsigned, unsigned);
};
class PixPixMap : public PixMap<RGB> {
 public:
  PixPixMap();
  PixPixMap(unsigned width, unsigned height, unsigned max_pixel_value);
};

std::ostream& operator<<(std::ostream& out, const Header& h) {
  out << h.format << '\n'
      << h.width << ' ' << h.height << '\n'
      << h.max_pixel_value << '\n';
  return out;
}

std::ostream& operator<<(std::ostream& out, const RGB& rgb) {
  out << rgb.r << ' ' << rgb.g << ' ' << rgb.b;
  return out;
}

template <class U>
std::ostream& operator<<(std::ostream& out, const PixMap<U>& pix_map) {
  out << pix_map.head;
  for (auto const& d : pix_map.data) {
    out << d << '\n';
  }
  return out;
}

template <class T>
PixMap<T>::PixMap(std::string format, unsigned width, unsigned height,
                  unsigned max_pixel_value) {
  head.format = format;
  head.width = width;
  head.height = height;
  head.max_pixel_value = max_pixel_value;

  data.resize(width * height);
  counter = 0;
}

template <class T>
PixMap<T>& PixMap<T>::operator<<(T val) {
  data.at(counter) = val;
  return *this;
}

template <class T>
PixMap<T>& PixMap<T>::set_pixel(unsigned i, unsigned j, T val) {
  data.at(i * head.width + j) = val;
  return *this;
}

PixBitMap::PixBitMap(unsigned width, unsigned height)
    : PixMap<unsigned>("P1", width, height, 1) {}

/* PixBitMap::PixBitMap(unsigned width, unsigned height, std::string type) { */
/*   if (type == "regular") { */
/*     PixMap("P4", width, height, 1); */
/*   } else if (type == "plain") { */
/*     PixBitMap(width, height); */
/*   } */
/* } */
PixGreyMap::PixGreyMap(unsigned width, unsigned height,
                       unsigned max_pixel_value)
    : PixMap<unsigned>("P2", width, height, max_pixel_value) {}

RGB::RGB() {
  r = 0;
  g = 0;
  b = 0;
}
RGB::RGB(unsigned red, unsigned green, unsigned blue) {
  r = red;
  g = green;
  b = blue;
}

PixPixMap::PixPixMap(unsigned width, unsigned height, unsigned max_pixel_value)
    : PixMap<RGB>("P3", width, height, max_pixel_value) {}
#endif  // PM_HPP
