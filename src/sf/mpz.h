#pragma once

#include <memory>
#include <string>

namespace sf {

  class mpz {
    mpz(void*);
    std::shared_ptr<void> impl;
  public:
    mpz();
    mpz(int);
    mpz(long long);
    operator std::string() const;
  };

}
