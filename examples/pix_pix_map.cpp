#include <fstream>
#include "ppm.hpp"

int main() {
  const unsigned MAX = 255;
  PixPixMap p(480, 270, MAX);
  std::ofstream file("test.ppm");
  for (unsigned y = 0; y < p.get_height(); ++y) {
    for (unsigned x = 0; x < p.get_width(); ++x) {
      p.set_pixel(x, y,
                  RGB((static_cast<float>(x) / p.get_width()) * MAX,
                      (static_cast<float>(y) / p.get_width()) * MAX, 51));
    }
  }
  file << p;
  return 0;
}
