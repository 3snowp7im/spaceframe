#include <mpreal.h>
#include "../sf/mpf.h"

void sf::mpf::init() {
  mpfr::mpreal::set_default_prec(128);
}

const sf::mpf& sf::mpf::pi() {
  static const auto pi = mpf(new mpfr::mpreal(mpfr::const_pi()));
  return pi;
}

sf::mpf::mpf(void* v) :
  impl(std::shared_ptr<void>(static_cast<mpfr::mpreal*>(v))) {
}

sf::mpf::mpf() :
  impl(std::shared_ptr<void>(new mpfr::mpreal)) {
}

sf::mpf::mpf(int v) :
  impl(std::shared_ptr<void>(new mpfr::mpreal(v))) {
}

sf::mpf::mpf(long v) :
  impl(std::shared_ptr<void>(new mpfr::mpreal(v))) {
}

sf::mpf::mpf(double v) :
  impl(std::shared_ptr<void>(new mpfr::mpreal(v))) {
}

sf::mpf::mpf(const std::string& v) :
  impl(std::shared_ptr<void>(new mpfr::mpreal(v))) {
}

sf::mpf sf::mpf::fmod(const mpf& x, const mpf& y) {
  auto res = mpfr::fmod(*static_cast<mpfr::mpreal*>(x.impl.get()), *static_cast<mpfr::mpreal*>(y.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::abs(const mpf& v) {
  auto res = mpfr::abs(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::trunc(const mpf& v) {
  auto res = mpfr::trunc(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::round(const mpf& v) {
  auto res = mpfr::round(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator-() const {
  auto res = -*static_cast<mpfr::mpreal*>(impl.get());
  return mpf(new mpfr::mpreal(res));
};

sf::mpf sf::mpf::operator+(const mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) + *static_cast<mpfr::mpreal*>(v.impl.get());
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator+(int v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) + v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator+(long v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) + v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator-(const mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) - *static_cast<mpfr::mpreal*>(v.impl.get());
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator-(int v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) - v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator-(long v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) - v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator*(const mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) * *static_cast<mpfr::mpreal*>(v.impl.get());
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator*(int v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) * v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator*(long v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) * v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator/(const mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) / *static_cast<mpfr::mpreal*>(v.impl.get());
  return sf::mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator/(int v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) / v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator/(long v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) / v;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator<<(int v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) << v;
  return mpf(new mpfr::mpreal(res));
}

bool sf::mpf::operator==(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) == *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator==(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) == v;
}

bool sf::mpf::operator==(long v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) == v;
}

bool sf::mpf::operator<(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) < *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator<(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) < v;
}

bool sf::mpf::operator<(long v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) < v;
}

bool sf::mpf::operator<=(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) <= *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator<=(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) <= v;
}

bool sf::mpf::operator<=(long v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) <= v;
}

bool sf::mpf::operator>(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) > *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator>(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) > v;
}

bool sf::mpf::operator>(long v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) > v;
}

bool sf::mpf::operator>=(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) >= *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator>=(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) >= v;
}

bool sf::mpf::operator>=(long v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) >= v;
}

sf::mpf::operator int() const {
  return static_cast<mpfr::mpreal*>(impl.get())->toLong(MPFR_RNDZ);
}

sf::mpf::operator long() const {
  return static_cast<mpfr::mpreal*>(impl.get())->toLong(MPFR_RNDZ);
}

sf::mpf::operator float() const {
  return static_cast<mpfr::mpreal*>(impl.get())->toFloat();
}

sf::mpf::operator double() const {
  return static_cast<mpfr::mpreal*>(impl.get())->toDouble();
}

sf::mpf sf::mpf::sqrt(const mpf& v) {
  auto res = mpfr::sqrt(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::sqrt(int v) {
  auto res = mpfr::sqrt(v);
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::sqrt(long v) {
  auto res = mpfr::sqrt(v);
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::acos(const mpf& v) {
  auto res = mpfr::acos(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::asin(const mpf& v) {
  auto res = mpfr::asin(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::atan(const mpf& v) {
  auto res = mpfr::atan(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::atan2(const mpf& y, const mpf& x) {
  auto res = mpfr::atan2(
    *static_cast<mpfr::mpreal*>(y.impl.get()),
    *static_cast<mpfr::mpreal*>(x.impl.get())
  );
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::cos(const mpf& v) {
  auto res = mpfr::cos(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::sin(const mpf& v) {
  auto res = mpfr::sin(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::tan(const mpf& v) {
  auto res = mpfr::tan(*static_cast<mpfr::mpreal*>(v.impl.get()));
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator+=(const mpf& v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) + *static_cast<mpfr::mpreal*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator+=(int v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) + v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator+=(long v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) + v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator-=(const mpf& v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) - *static_cast<mpfr::mpreal*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator-=(int v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) - v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator-=(long v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) - v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator*=(const mpf& v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) * *static_cast<mpfr::mpreal*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator*=(int v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) * v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator*=(long v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) * v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator/=(const mpf& v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) / *static_cast<mpfr::mpreal*>(v.impl.get()));
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator/=(int v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) / v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::mpf::operator/=(long v) {
  auto res = new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) / v);
  impl.reset(res);
  return *this;
}

sf::mpf sf::operator+(int a, const sf::mpf& b) {
  return mpf(a) + b;
}

sf::mpf sf::operator+(long a, const sf::mpf& b) {
  return mpf(a) + b;
}

sf::mpf sf::operator-(int a, const sf::mpf& b) {
  return mpf(a) - b;
}

sf::mpf sf::operator-(long a, const sf::mpf& b) {
  return mpf(a) - b;
}

sf::mpf sf::operator*(int a, const sf::mpf& b) {
  return mpf(a) * b;
}

sf::mpf sf::operator*(long a, const sf::mpf& b) {
  return mpf(a) * b;
}

sf::mpf sf::operator/(int a, const sf::mpf& b) {
  return mpf(a) / b;
}

sf::mpf sf::operator/(long a, const sf::mpf& b) {
  return mpf(a) / b;
}

std::string std::to_string(const sf::mpf& v) {
  return static_cast<mpfr::mpreal*>(v.impl.get())->toString();
}
