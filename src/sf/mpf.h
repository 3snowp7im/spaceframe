#pragma once

#include <memory>
#include <string>

namespace sf {

  class mpf {
    mpf(void*);
    std::shared_ptr<void> impl;
  public:
    static const mpf& pi();
    mpf();
    mpf(int);
    mpf(long long);
    mpf(double);
    mpf operator-() const;
    mpf operator+(const mpf&) const;
    mpf operator+=(const mpf&) const;
    mpf operator-(const mpf&) const;
    mpf operator*(const mpf&) const;
    mpf operator*(int) const;
    mpf operator*(long long) const;
    mpf operator/(int) const;
    mpf operator/(const mpf&) const;
    mpf operator<<(int) const;
    mpf operator/=(const mpf&) const;
    bool operator==(const mpf&) const;
    bool operator==(int) const;
    bool operator<(const mpf&) const;
    bool operator<(int) const;
    bool operator<=(const mpf&) const;
    bool operator<=(int) const;
    bool operator>(const mpf&) const;
    bool operator>(int) const;
    bool operator>=(const mpf&) const;
    bool operator>=(int) const;
    operator long long() const;
    operator float() const;
    operator double() const;
    operator std::string() const;
    friend mpf operator+(int, const mpf&);
    friend mpf operator-(int, const mpf&);
    friend mpf operator*(int, const mpf&);
    friend mpf operator/(int, const mpf&);
    static mpf sqrt(const mpf&);
    static mpf sqrt(int);
    static mpf acos(const mpf&);
    static mpf atan2(const mpf&, const mpf&);
    static mpf cos(const mpf&);
    static mpf sin(const mpf&);
    static mpf tan(const mpf&);
  };

  sf::mpf operator-(int, const sf::mpf&);
  sf::mpf operator+(int, const sf::mpf&);
  sf::mpf operator*(int, const sf::mpf&);
  sf::mpf operator/(int, const sf::mpf&);

}

