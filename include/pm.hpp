#ifndef PM_HPP
#define PM_HPP

#include <iostream>
#include <string>

struct Header {
  std::string format;
  unsigned width, height;
  unsigned max_pixel_value;

  friend std::ostream& operator<<(std::ostream&, Header&);
};

class PixMap {
  Header head;
  unsigned* data;
  unsigned counter, limit;

 public:
  PixMap();
  PixMap(std::string, unsigned, unsigned, unsigned, unsigned = 1);
  ~PixMap();

  friend std::ostream& operator<<(std::ostream&, PixMap&);

  void operator<<(unsigned);

  void set_format();
  void set_width();
  void set_height();
  void set_max();
};
class PixBitMap : public PixMap {
 public:
  PixBitMap();
  PixBitMap(unsigned, unsigned);
  PixBitMap(unsigned, unsigned, std::string);
};

std::ostream& operator<<(std::ostream& out, Header& h) {
  out << h.format << '\n'
      << h.width << ' ' << h.height << '\n'
      << h.max_pixel_value << '\n';
  return out;
}

PixMap::PixMap(std::string format, unsigned width, unsigned height,
               unsigned max_pixel_value, unsigned division_factor) {
  head.format = format;
  head.width = width;
  head.height = height;
  head.max_pixel_value = max_pixel_value;

  if (division_factor == 1) {
    limit = width * height;
  } else {
    limit = width * height / division_factor;
    if (width * height % division_factor != 0) {
      limit++;
    }
  }

  data = new unsigned[limit];
  counter = 0;
}

PixMap::~PixMap() { delete[] data; }

void PixMap::operator<<(unsigned val) { *(data + counter++) = val; }

std::ostream& operator<<(std::ostream& out, PixMap& pix_map) {
  out << pix_map.head;
  for (auto i = pix_map.data, l = pix_map.data + pix_map.limit; i < l; ++i) {
    out << *i << '\n';
  }
  return out;
}

PixBitMap::PixBitMap(unsigned width, unsigned height)
    : PixMap("P1", width, height, 1) {}

PixBitMap::PixBitMap(unsigned width, unsigned height, std::string type) {
  if (type == "regular") {
    PixMap("P4", width, height, 1, 8);
  } else if (type == "plain") {
    PixBitMap(width, height);
  }
}
#endif  // PM_HPP
