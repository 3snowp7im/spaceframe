#include <sf/face.h>
#include <sf/mpf.h>
#include <sf/spheroid.h>
#include <sf/sf.h>

void sf::init() {
  mpf::init();
  face::init();
  spheroid::init();
}
