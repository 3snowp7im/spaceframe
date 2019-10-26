#include <sf/sf.h>
#include "mpf.h"
#include "spheroid.h"

void sf::init() {
  mpf::init();
  tetra::init();
  spheroid::init();
}
