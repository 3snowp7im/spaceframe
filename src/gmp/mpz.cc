#include <gmpxx.h>
#include <sf/mpf.h>
#include <sf/mpz.h>

sf::mpz::mpz(void* v) :
  impl(std::shared_ptr<void>(static_cast<mpz_class*>(v))) {
}

sf::mpz::mpz(const mpf& v) :
  impl(std::shared_ptr<void>(new mpz_class)) {
  mpz_class& m = *static_cast<mpz_class*>(impl.get());
  auto t = mpf::abs(mpf::trunc(v));
  size_t place = 0;
  while (t > 0) {
    m += static_cast<int>(mpf::fmod(t, 2)) << (place++);
    t = mpf::trunc(t / 2);
  }
  if (v < 0) {
    t *= -1;
  }
}

sf::mpz::mpz(int v) :
  impl(std::shared_ptr<void>(new mpz_class(v))) {
}

sf::mpz::mpz(unsigned v) :
  impl(std::shared_ptr<void>(new mpz_class(v))) {
}

sf::mpz::mpz(long v) :
  impl(std::shared_ptr<void>(new mpz_class(v))) {
}

sf::mpz::mpz(long unsigned v) :
  impl(std::shared_ptr<void>(new mpz_class(v))) {
}

size_t sf::mpz::byte_size() const {
  return mpz_sizeinbase(static_cast<mpz_class*>(impl.get())->get_mpz_t(), 256);
}

sf::mpz sf::mpz::pow(const mpz& b, long unsigned e) {
  auto res = new mpz_class;
  mpz_pow_ui(res->get_mpz_t(), static_cast<mpz_class*>(b.impl.get())->get_mpz_t(), e);
  return mpz(res);
}

sf::mpz sf::mpz::operator-() const {
  auto res = -*static_cast<mpz_class*>(impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator+(const mpz& v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) + *static_cast<mpz_class*>(v.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator+(int v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) + v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator+(unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) + v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator+(long v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) + v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator+(long unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) + v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator-(const mpz& v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) - *static_cast<mpz_class*>(v.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator-(int v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) - v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator-(unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) - v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator-(long v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) - v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator-(long unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) - v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator*(const mpz& v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) * *static_cast<mpz_class*>(v.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator*(int v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) * v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator*(unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) * v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator*(long v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) * v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator*(long unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) * v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator/(const mpz& v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) / *static_cast<mpz_class*>(v.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator/(int v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) / v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator/(unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) / v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator/(long v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) / v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator/(long unsigned v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) / v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator%(const mpz& v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) % *static_cast<mpz_class*>(v.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator%(int m) const {
  auto res = *static_cast<mpz_class*>(impl.get()) % m;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator%(unsigned m) const {
  auto res = *static_cast<mpz_class*>(impl.get()) % m;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator%(long m) const {
  auto res = *static_cast<mpz_class*>(impl.get()) % m;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator%(long unsigned m) const {
  auto res = *static_cast<mpz_class*>(impl.get()) % m;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator&(const mpz& b) const {
  auto res = *static_cast<mpz_class*>(impl.get()) & *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator<<(int v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) << v;
  return mpz(new mpz_class(res));
}

sf::mpz sf::mpz::operator>>(int v) const {
  auto res = *static_cast<mpz_class*>(impl.get()) >> v;
  return mpz(new mpz_class(res));
}

bool sf::mpz::operator==(const mpz& v) const {
  return *static_cast<mpz_class*>(impl.get()) == *static_cast<mpz_class*>(v.impl.get());
}

bool sf::mpz::operator==(int v) const {
  return *static_cast<mpz_class*>(impl.get()) == v;
}

bool sf::mpz::operator==(unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) == v;
}

bool sf::mpz::operator==(long v) const {
  return *static_cast<mpz_class*>(impl.get()) == v;
}

bool sf::mpz::operator==(long unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) == v;
}

bool sf::mpz::operator!=(const mpz& v) const {
  return *static_cast<mpz_class*>(impl.get()) != *static_cast<mpz_class*>(v.impl.get());
}

bool sf::mpz::operator!=(int v) const {
  return *static_cast<mpz_class*>(impl.get()) != v;
}

bool sf::mpz::operator!=(unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) != v;
}

bool sf::mpz::operator!=(long v) const {
  return *static_cast<mpz_class*>(impl.get()) != v;
}

bool sf::mpz::operator!=(long unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) == v;
}

bool sf::mpz::operator<(const mpz& v) const {
  return *static_cast<mpz_class*>(impl.get()) < *static_cast<mpz_class*>(v.impl.get());
}

bool sf::mpz::operator<(int v) const {
  return *static_cast<mpz_class*>(impl.get()) < v;
}

bool sf::mpz::operator<(unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) < v;
}

bool sf::mpz::operator<(long v) const {
  return *static_cast<mpz_class*>(impl.get()) < v;
}

bool sf::mpz::operator<(long unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) < v;
}

bool sf::mpz::operator<=(const mpz& v) const {
  return *static_cast<mpz_class*>(impl.get()) <= *static_cast<mpz_class*>(v.impl.get());
}

bool sf::mpz::operator<=(int v) const {
  return *static_cast<mpz_class*>(impl.get()) <= v;
}

bool sf::mpz::operator<=(unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) <= v;
}

bool sf::mpz::operator<=(long v) const {
  return *static_cast<mpz_class*>(impl.get()) <= v;
}

bool sf::mpz::operator<=(long unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) <= v;
}

bool sf::mpz::operator>(const mpz& v) const {
  return *static_cast<mpz_class*>(impl.get()) > *static_cast<mpz_class*>(v.impl.get());
}

bool sf::mpz::operator>(int v) const {
  return *static_cast<mpz_class*>(impl.get()) > v;
}

bool sf::mpz::operator>(unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) > v;
}

bool sf::mpz::operator>(long v) const {
  return *static_cast<mpz_class*>(impl.get()) > v;
}

bool sf::mpz::operator>(long unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) > v;
}

bool sf::mpz::operator>=(const mpz& v) const {
  return *static_cast<mpz_class*>(impl.get()) >= *static_cast<mpz_class*>(v.impl.get());
}

bool sf::mpz::operator>=(int v) const {
  return *static_cast<mpz_class*>(impl.get()) >= v;
}

bool sf::mpz::operator>=(unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) >= v;
}

bool sf::mpz::operator>=(long v) const {
  return *static_cast<mpz_class*>(impl.get()) >= v;
}

bool sf::mpz::operator>=(long unsigned v) const {
  return *static_cast<mpz_class*>(impl.get()) >= v;
}

sf::mpz::operator int() const {
  return static_cast<mpz_class*>(impl.get())->get_si();
}

sf::mpz::operator unsigned() const {
  return static_cast<mpz_class*>(impl.get())->get_ui();
}

sf::mpz::operator long() const {
  return static_cast<mpz_class*>(impl.get())->get_si();
}

sf::mpz::operator long unsigned() const {
  return static_cast<mpz_class*>(impl.get())->get_ui();
}

sf::mpz::operator std::vector<std::bitset<8>>() const {
  std::vector<std::bitset<8>> bytes(byte_size());
  mpz bit = 1;
  for (int i = bytes.size() - 1; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      if ((*this & bit) != 0) {
        bytes[i] |= 1 << j;
      }
      bit <<= 1;
    }
  }
  return bytes;
}

sf::mpz sf::mpz::operator+=(const mpz& v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) + *static_cast<mpz_class*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator+=(int v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) + v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator+=(unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) + v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator+=(long v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) + v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator+=(long unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) + v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator-=(const mpz& v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) - *static_cast<mpz_class*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator-=(int v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) - v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator-=(unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) - v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator-=(long v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) - v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator-=(long unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) - v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator*=(const mpz& v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) * *static_cast<mpz_class*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator*=(int v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) * v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator*=(unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) * v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator*=(long v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) * v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator*=(long unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) * v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator/=(const mpz& v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) / *static_cast<mpz_class*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator/=(int v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) / v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator/=(unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) / v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator/=(long v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) / v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator/=(long unsigned v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) / v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator<<=(int v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) << v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::mpz::operator>>=(int v) {
  auto res = new mpz_class(*static_cast<mpz_class*>(impl.get()) >> v);
  impl.reset(res);
  return *this;
}

sf::mpz sf::operator+(int a, const mpz& b) {
  auto res = a + *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator+(unsigned a, const mpz& b) {
  auto res = a + *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator+(long a, const mpz& b) {
  auto res = a + *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator+(long unsigned a, const mpz& b) {
  auto res = a + *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator-(int a, const mpz& b) {
  auto res = a - *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator-(unsigned a, const mpz& b) {
  auto res = a - *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator-(long a, const mpz& b) {
  auto res = a - *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator-(long unsigned a, const mpz& b) {
  auto res = a - *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator*(int a, const mpz& b) {
  auto res = a * *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator*(unsigned a, const mpz& b) {
  auto res = a * *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator*(long a, const mpz& b) {
  auto res = a * *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator*(long unsigned a, const mpz& b) {
  auto res = a * *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator/(int a, const mpz& b) {
  auto res = a / *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator/(unsigned a, const mpz& b) {
  auto res = a / *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator/(long a, const mpz& b) {
  auto res = a / *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

sf::mpz sf::operator/(long unsigned a, const mpz& b) {
  auto res = a / *static_cast<mpz_class*>(b.impl.get());
  return mpz(new mpz_class(res));
}

bool sf::operator==(int a, const mpz& b) {
  return a == *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator==(unsigned a, const mpz& b) {
  return a == *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator==(long a, const mpz& b) {
  return a == *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator==(long unsigned a, const mpz& b) {
  return a == *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<(int a, const mpz& b) {
  return a < *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<(unsigned a, const mpz& b) {
  return a < *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<(long a, const mpz& b) {
  return a < *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<(long unsigned a, const mpz& b) {
  return a < *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<=(int a, const mpz& b) {
  return a <= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<=(unsigned a, const mpz& b) {
  return a <= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<=(long a, const mpz& b) {
  return a <= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator<=(long unsigned a, const mpz& b) {
  return a <= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>(int a, const mpz& b) {
  return a <= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>(unsigned a, const mpz& b) {
  return a > *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>(long a, const mpz& b) {
  return a > *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>(long unsigned a, const mpz& b) {
  return a > *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>=(int a, const mpz& b) {
  return a >= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>=(unsigned a, const mpz& b) {
  return a >= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>=(long a, const mpz& b) {
  return a >= *static_cast<mpz_class*>(b.impl.get());
}

bool sf::operator>=(long unsigned a, const mpz& b) {
  return a >= *static_cast<mpz_class*>(b.impl.get());
}

std::string sf::mpz::to_string() const {
  return static_cast<mpz_class*>(impl.get())->get_str();
}
