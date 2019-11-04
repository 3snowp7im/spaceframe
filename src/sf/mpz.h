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
    mpz(unsigned);
    mpz(long);
    mpz(unsigned long);
    mpz(const mpf&);
    mpz operator+(const mpz&) const;
    mpz operator+(int) const;
    mpz operator+(unsigned) const;
    mpz operator+(long) const;
    mpz operator+(unsigned long) const;
    mpz operator-(const mpz&) const;
    mpz operator-(int) const;
    mpz operator-(unsigned) const;
    mpz operator-(long) const;
    mpz operator-(unsigned long) const;
    mpz operator*(const mpz&) const;
    mpz operator*(int) const;
    mpz operator*(unsigned) const;
    mpz operator*(long) const;
    mpz operator*(unsigned long) const;
    mpz operator/(const mpz&) const;
    mpz operator/(int) const;
    mpz operator/(unsigned) const;
    mpz operator/(long) const;
    mpz operator/(unsigned long) const;
    mpz operator%(const mpz&) const;
    mpz operator%(int) const;
    mpz operator%(unsigned) const;
    mpz operator%(long) const;
    mpz operator%(unsigned long) const;
    mpz operator<<(int) const;
    bool operator==(const mpz&) const;
    bool operator==(int) const;
    bool operator==(unsigned) const;
    bool operator==(long) const;
    bool operator==(unsigned long) const;
    bool operator<(const mpz&) const;
    bool operator<(int) const;
    bool operator<(unsigned) const;
    bool operator<(long) const;
    bool operator<(unsigned long) const;
    bool operator<=(const mpz&) const;
    bool operator<=(int) const;
    bool operator<=(unsigned) const;
    bool operator<=(long) const;
    bool operator<=(unsigned long) const;
    bool operator>(const mpz&) const;
    bool operator>(int) const;
    bool operator>(unsigned) const;
    bool operator>(long) const;
    bool operator>(unsigned long) const;
    bool operator>=(const mpz&) const;
    bool operator>=(int) const;
    bool operator>=(unsigned) const;
    bool operator>=(long) const;
    bool operator>=(unsigned long) const;
    operator int() const;
    operator unsigned() const;
    operator long() const;
    operator unsigned long() const;
    mpz operator+=(const mpz&);
    mpz operator+=(int);
    mpz operator+=(unsigned);
    mpz operator+=(long);
    mpz operator+=(unsigned long);
    mpz operator-=(const mpz&);
    mpz operator-=(int);
    mpz operator-=(unsigned);
    mpz operator-=(long);
    mpz operator-=(unsigned long);
    mpz operator*=(const mpz&);
    mpz operator*=(int);
    mpz operator*=(unsigned);
    mpz operator*=(long);
    mpz operator*=(unsigned long);
    mpz operator/=(const mpz&);
    mpz operator/=(int);
    mpz operator/=(unsigned);
    mpz operator/=(long);
    mpz operator/=(unsigned long);
    friend mpz operator+(int, const mpz&);
    friend mpz operator+(unsigned, const mpz&);
    friend mpz operator+(long, const mpz&);
    friend mpz operator+(unsigned long, const mpz&);
    friend mpz operator-(int, const mpz&);
    friend mpz operator-(unsigned, const mpz&);
    friend mpz operator-(long, const mpz&);
    friend mpz operator-(unsigned long, const mpz&);
    friend mpz operator*(int, const mpz&);
    friend mpz operator*(unsigned, const mpz&);
    friend mpz operator*(long, const mpz&);
    friend mpz operator*(unsigned long, const mpz&);
    friend mpz operator/(int, const mpz&);
    friend mpz operator/(unsigned, const mpz&);
    friend mpz operator/(long, const mpz&);
    friend mpz operator/(unsigned long, const mpz&);
    friend std::string std::to_string(const mpz&);
  };

  mpz operator+(int, const mpz&);
  mpz operator+(unsigned, const mpz&);
  mpz operator+(long, const mpz&);
  mpz operator+(unsigned long, const mpz&);
  mpz operator-(int, const mpz&);
  mpz operator-(unsigned, const mpz&);
  mpz operator-(long, const mpz&);
  mpz operator-(unsigned long, const mpz&);
  mpz operator*(int, const mpz&);
  mpz operator*(unsigned, const mpz&);
  mpz operator*(long, const mpz&);
  mpz operator*(unsigned long, const mpz&);
  mpz operator/(int, const mpz&);
  mpz operator/(unsigned, const mpz&);
  mpz operator/(long, const mpz&);
  mpz operator/(unsigned long, const mpz&);

}
