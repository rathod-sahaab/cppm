#include <fstream>
#include "./include/pm.hpp"

int main() {
  const unsigned MAX = 255;
  PixPixMap p(512, 512, MAX);
  std::ofstream file("test.ppm");
  for (unsigned i = 0; i < 512; ++i) {
    for (unsigned j = 0; j < 512; ++j) {
      p.set_pixel(i, j, RGB(i % MAX, j % MAX, 0));
    }
  }
  file << p;
  return 0;
}
