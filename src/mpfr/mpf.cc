#include <mpreal.h>
#include "../sf/mpf.h"

const sf::mpf& sf::mpf::pi() {
  static const auto pi = mpf(new mpfr::mpreal(mpfr::const_pi()));
  return pi;
}

sf::mpf::mpf(void* v)
  : impl(std::shared_ptr<void>(static_cast<mpfr::mpreal*>(v)))
{
}

sf::mpf::mpf()
  : impl(std::shared_ptr<void>(new mpfr::mpreal(0)))
{
}

sf::mpf::mpf(int v)
  : impl(std::shared_ptr<void>(new mpfr::mpreal(v)))
{
}

sf::mpf::mpf(double v)
  : impl(std::shared_ptr<void>(new mpfr::mpreal(v)))
{
}

sf::mpf sf::mpf::operator-() const {
  auto res = -*static_cast<mpfr::mpreal*>(impl.get());
  return mpf(new mpfr::mpreal(res));
};

sf::mpf sf::mpf::operator+(const sf::mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) + *static_cast<mpfr::mpreal*>(v.impl.get());
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator+=(const sf::mpf& v) const {
  return *this + v;
}

sf::mpf sf::mpf::operator-(const sf::mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) - *static_cast<mpfr::mpreal*>(v.impl.get());
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator*(const sf::mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) * *static_cast<mpfr::mpreal*>(v.impl.get());
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator*(int b) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) * b;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator*(long long b) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) * b;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator/(const mpf& v) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) / *static_cast<mpfr::mpreal*>(v.impl.get());
  return sf::mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator/(int b) const {
  auto res = *static_cast<mpfr::mpreal*>(impl.get()) / b;
  return mpf(new mpfr::mpreal(res));
}

sf::mpf sf::mpf::operator/=(const mpf& v) const {
  return *this / v;
}

bool sf::mpf::operator==(const mpf& v) const {
  return mpf(new mpfr::mpreal(*static_cast<mpfr::mpreal*>(impl.get()) == *static_cast<mpfr::mpreal*>(v.impl.get())));
}

bool sf::mpf::operator==(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) == v;
}

bool sf::mpf::operator<(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) < *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator<(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) < v;
}

bool sf::mpf::operator<=(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) <= *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator<=(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) <= v;
}

bool sf::mpf::operator>(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) > *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator>(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) > v;
}

bool sf::mpf::operator>=(const mpf& v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) >= *static_cast<mpfr::mpreal*>(v.impl.get());
}

bool sf::mpf::operator>=(int v) const {
  return *static_cast<mpfr::mpreal*>(impl.get()) >= v;
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

sf::mpf sf::mpf::acos(const mpf& v) {
  auto res = mpfr::acos(*static_cast<mpfr::mpreal*>(v.impl.get()));
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

sf::mpf sf::operator-(int a, const sf::mpf& b) {
  auto res = a - *static_cast<mpfr::mpreal*>(b.impl.get());
  return sf::mpf(new mpfr::mpreal(res));
}

sf::mpf sf::operator+(int a, const sf::mpf& b) {
  auto res = a + *static_cast<mpfr::mpreal*>(b.impl.get());
  return sf::mpf(new mpfr::mpreal(res));
}

sf::mpf sf::operator*(int a, const sf::mpf& b) {
  auto res = a * *static_cast<mpfr::mpreal*>(b.impl.get());
  return sf::mpf(new mpfr::mpreal(res));
}

sf::mpf sf::operator/(int a, const sf::mpf& b) {
  auto res = a / *static_cast<mpfr::mpreal*>(b.impl.get());
  return sf::mpf(new mpfr::mpreal(res));
}
