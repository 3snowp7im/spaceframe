#pragma once

#include <memory>
#include <string>

namespace sf {

  class mpz;

}

namespace std {

  string to_string(const sf::mpz&);

}

namespace sf {

  class mpf;

  class mpz {
    mpz(void*);
    std::shared_ptr<void> impl;
  public:
    static mpz pow(const mpz&, unsigned long);
    mpz(int);
    mpz(long);
    mpz(const mpf&);
    mpz operator+(const mpz&) const;
    mpz operator+(int) const;
    mpz operator+(long) const;
    mpz operator-(const mpz&) const;
    mpz operator-(int) const;
    mpz operator-(long) const;
    mpz operator*(const mpz&) const;
    mpz operator*(int) const;
    mpz operator*(long) const;
    mpz operator/(const mpz&) const;
    mpz operator/(int) const;
    mpz operator/(long) const;
    mpz operator%(const mpz&) const;
    mpz operator%(int) const;
    mpz operator%(long) const;
    operator int() const;
    operator long() const;
    friend mpz operator+(int, const mpz&);
    friend mpz operator+(long, const mpz&);
    friend mpz operator-(int, const mpz&);
    friend mpz operator-(long, const mpz&);
    friend mpz operator*(int, const mpz&);
    friend mpz operator*(long, const mpz&);
    friend mpz operator/(int, const mpz&);
    friend mpz operator/(long, const mpz&);
    friend std::string std::to_string(const mpz&);
  };

  mpz operator+(int, const mpz&);
  mpz operator+(long, const mpz&);
  mpz operator-(int, const mpz&);
  mpz operator-(long, const mpz&);
  mpz operator*(int, const mpz&);
  mpz operator*(long, const mpz&);
  mpz operator/(int, const mpz&);
  mpz operator/(long, const mpz&);

}
