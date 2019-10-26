#pragma once

#include <memory>
#include <string>
#include "mpz.h"

namespace sf {

  class mpf;

}

namespace std {

  string to_string(const sf::mpf&);

}

namespace sf {

  class mpf {
    static void init();
    mpf(void*);
    std::shared_ptr<void> impl;
  public:
    static const mpf& pi();
    static mpf abs(const mpf&);
    static mpf sqrt(const mpf&);
    static mpf sqrt(int);
    static mpf sqrt(long);
    static mpf acos(const mpf&);
    static mpf asin(const mpf&);
    static mpf atan(const mpf&);
    static mpf atan2(const mpf&, const mpf&);
    static mpf cos(const mpf&);
    static mpf sin(const mpf&);
    static mpf tan(const mpf&);
    static mpf fmod(const mpf&, const mpf&);
    static mpf trunc(const mpf&);
    static mpf round(const mpf&);
    mpf();
    mpf(int);
    mpf(long);
    mpf(double);
    mpf(const std::string&);
    mpf operator-() const;
    mpf operator+(const mpf&) const;
    mpf operator+(int) const;
    mpf operator+(long) const;
    mpf operator-(const mpf&) const;
    mpf operator-(int) const;
    mpf operator-(long) const;
    mpf operator*(const mpf&) const;
    mpf operator*(int) const;
    mpf operator*(long) const;
    mpf operator/(const mpf&) const;
    mpf operator/(int) const;
    mpf operator/(long) const;
    mpf operator<<(int) const;
    bool operator==(const mpf&) const;
    bool operator==(int) const;
    bool operator==(long) const;
    bool operator<(const mpf&) const;
    bool operator<(int) const;
    bool operator<(long) const;
    bool operator<=(const mpf&) const;
    bool operator<=(int) const;
    bool operator<=(long) const;
    bool operator>(const mpf&) const;
    bool operator>(int) const;
    bool operator>(long) const;
    bool operator>=(const mpf&) const;
    bool operator>=(int) const;
    bool operator>=(long) const;
    operator int() const;
    operator long() const;
    operator float() const;
    operator double() const;
    mpf operator+=(const mpf&);
    mpf operator+=(int);
    mpf operator+=(long);
    mpf operator-=(const mpf&);
    mpf operator-=(int);
    mpf operator-=(long);
    mpf operator*=(const mpf&);
    mpf operator*=(int);
    mpf operator*=(long);
    mpf operator/=(const mpf&);
    mpf operator/=(int);
    mpf operator/=(long);
    friend mpf operator+(int, const mpf&);
    friend mpf operator+(long, const mpf&);
    friend mpf operator-(int, const mpf&);
    friend mpf operator-(long, const mpf&);
    friend mpf operator*(int, const mpf&);
    friend mpf operator*(long, const mpf&);
    friend mpf operator/(int, const mpf&);
    friend mpf operator/(long, const mpf&);
    friend void sf::init();
    friend std::string std::to_string(const mpf&);
  };

  mpf operator+(int, const mpf&);
  mpf operator+(long, const mpf&);
  mpf operator-(int, const mpf&);
  mpf operator-(long, const mpf&);
  mpf operator*(int, const mpf&);
  mpf operator*(long, const mpf&);
  mpf operator/(int, const mpf&);
  mpf operator/(long, const mpf&);

}
