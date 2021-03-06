#pragma once

#include <memory>
#include <sf/sf.h>
#include <string>

namespace sf {

  class mpz;

  class mpf {
    static void init();
    mpf(void*);
    std::shared_ptr<void> impl;
  public:
    static const mpf& pi();
    static mpf abs(const mpf&);
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
    static mpf sqrt(const mpf&);
    static mpf sqrt(int);
    mpf();
    mpf(int);
    mpf(unsigned);
    mpf(long);
    mpf(long unsigned);
    mpf(float);
    mpf(double);
    mpf(const mpz&);
    mpf(const std::string&);
    mpf operator-() const;
    mpf operator+(const mpf&) const;
    mpf operator+(int) const;
    mpf operator+(unsigned) const;
    mpf operator+(long) const;
    mpf operator+(long unsigned) const;
    mpf operator-(const mpf&) const;
    mpf operator-(int) const;
    mpf operator-(unsigned) const;
    mpf operator-(long) const;
    mpf operator-(long unsigned) const;
    mpf operator*(const mpf&) const;
    mpf operator*(int) const;
    mpf operator*(unsigned) const;
    mpf operator*(long) const;
    mpf operator*(long unsigned) const;
    mpf operator/(const mpf&) const;
    mpf operator/(int) const;
    mpf operator/(unsigned) const;
    mpf operator/(long) const;
    mpf operator/(long unsigned) const;
    mpf operator<<(int) const;
    mpf operator>>(int) const;
    bool operator==(const mpf&) const;
    bool operator==(int) const;
    bool operator==(unsigned) const;
    bool operator==(long) const;
    bool operator==(long unsigned) const;
    bool operator!=(const mpf&) const;
    bool operator!=(int) const;
    bool operator!=(unsigned) const;
    bool operator!=(long) const;
    bool operator!=(long unsigned) const;
    bool operator<(const mpf&) const;
    bool operator<(int) const;
    bool operator<(unsigned) const;
    bool operator<(long) const;
    bool operator<(long unsigned) const;
    bool operator<=(const mpf&) const;
    bool operator<=(int) const;
    bool operator<=(unsigned) const;
    bool operator<=(long) const;
    bool operator<=(long unsigned) const;
    bool operator>(const mpf&) const;
    bool operator>(int) const;
    bool operator>(unsigned) const;
    bool operator>(long) const;
    bool operator>(long unsigned) const;
    bool operator>=(const mpf&) const;
    bool operator>=(int) const;
    bool operator>=(unsigned) const;
    bool operator>=(long) const;
    bool operator>=(long unsigned) const;
    operator int() const;
    operator unsigned() const;
    operator long() const;
    operator long unsigned() const;
    operator float() const;
    operator double() const;
    mpf operator+=(const mpf&);
    mpf operator+=(int);
    mpf operator+=(unsigned);
    mpf operator+=(long);
    mpf operator+=(long unsigned);
    mpf operator-=(const mpf&);
    mpf operator-=(int);
    mpf operator-=(unsigned);
    mpf operator-=(long);
    mpf operator-=(long unsigned);
    mpf operator*=(const mpf&);
    mpf operator*=(int);
    mpf operator*=(unsigned);
    mpf operator*=(long);
    mpf operator*=(long unsigned);
    mpf operator/=(const mpf&);
    mpf operator/=(int);
    mpf operator/=(unsigned);
    mpf operator/=(long);
    mpf operator/=(long unsigned);
    mpf operator<<=(int);
    mpf operator>>=(int);
    friend mpf operator+(int, const mpf&);
    friend mpf operator+(unsigned, const mpf&);
    friend mpf operator+(long, const mpf&);
    friend mpf operator+(long unsigned, const mpf&);
    friend mpf operator-(int, const mpf&);
    friend mpf operator-(unsigned, const mpf&);
    friend mpf operator-(long, const mpf&);
    friend mpf operator-(long unsigned, const mpf&);
    friend mpf operator*(int, const mpf&);
    friend mpf operator*(unsigned, const mpf&);
    friend mpf operator*(long, const mpf&);
    friend mpf operator*(long unsigned, const mpf&);
    friend mpf operator/(int, const mpf&);
    friend mpf operator/(unsigned, const mpf&);
    friend mpf operator/(long, const mpf&);
    friend mpf operator/(long unsigned, const mpf&);
    friend bool operator==(int, const mpf&);
    friend bool operator==(unsigned, const mpf&);
    friend bool operator==(long, const mpf&);
    friend bool operator==(long unsigned, const mpf&);
    friend bool operator<(int, const mpf&);
    friend bool operator<(unsigned, const mpf&);
    friend bool operator<(long, const mpf&);
    friend bool operator<(long unsigned, const mpf&);
    friend bool operator<=(int, const mpf&);
    friend bool operator<=(unsigned, const mpf&);
    friend bool operator<=(long, const mpf&);
    friend bool operator<=(long unsigned, const mpf&);
    friend bool operator>(int, const mpf&);
    friend bool operator>(unsigned, const mpf&);
    friend bool operator>(long, const mpf&);
    friend bool operator>(long unsigned, const mpf&);
    friend bool operator>=(int, const mpf&);
    friend bool operator>=(unsigned, const mpf&);
    friend bool operator>=(long, const mpf&);
    friend bool operator>=(long unsigned, const mpf&);
    friend void sf::init();
    std::string to_string() const;
  };

  mpf operator+(int, const mpf&);
  mpf operator+(unsigned, const mpf&);
  mpf operator+(long, const mpf&);
  mpf operator+(long unsigned, const mpf&);
  mpf operator-(int, const mpf&);
  mpf operator-(unsigned, const mpf&);
  mpf operator-(long, const mpf&);
  mpf operator-(long unsigned, const mpf&);
  mpf operator*(int, const mpf&);
  mpf operator*(unsigned, const mpf&);
  mpf operator*(long, const mpf&);
  mpf operator*(long unsigned, const mpf&);
  mpf operator/(int, const mpf&);
  mpf operator/(unsigned, const mpf&);
  mpf operator/(long, const mpf&);
  mpf operator/(long unsigned, const mpf&);
  bool operator==(int, const mpf&);
  bool operator==(unsigned, const mpf&);
  bool operator==(long, const mpf&);
  bool operator==(long unsigned, const mpf&);
  bool operator<(int, const mpf&);
  bool operator<(unsigned, const mpf&);
  bool operator<(long, const mpf&);
  bool operator<(long unsigned, const mpf&);
  bool operator<=(int, const mpf&);
  bool operator<=(unsigned, const mpf&);
  bool operator<=(long, const mpf&);
  bool operator<=(long unsigned, const mpf&);
  bool operator>(int, const mpf&);
  bool operator>(unsigned, const mpf&);
  bool operator>(long, const mpf&);
  bool operator>(long unsigned, const mpf&);
  bool operator>=(int, const mpf&);
  bool operator>=(unsigned, const mpf&);
  bool operator>=(long, const mpf&);
  bool operator>=(long unsigned, const mpf&);

}
