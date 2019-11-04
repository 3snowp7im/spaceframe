#include <sf/sf.h>
#include "face.h"
#include "mpf.h"
#include "spheroid.h"

void sf::init() {
  mpf::init();
  face::init();
  spheroid::init();
}
