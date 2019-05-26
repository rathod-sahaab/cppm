#include <fstream>
#include "ppm.hpp"

int main() {
  PixPixMap p(1024, 768, 255);
  p.fill(RGB(0x21, 0x21, 0x21));

  std::ofstream image("fill_test.ppm");
  image << p;
  image.close();

  return 0;
}
