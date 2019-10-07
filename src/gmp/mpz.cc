#include <gmpxx.h>
#include "../sf/mpz.h"

sf::mpz::mpz(void* v)
  : impl(std::shared_ptr<void>(static_cast<mpz_class*>(v)))
{
}

sf::mpz::mpz()
  : impl(std::shared_ptr<void>(new mpz_class(0)))
{
}

sf::mpz::mpz(int v)
  : impl(std::shared_ptr<void>(new mpz_class(v)))
{
}

sf::mpz::mpz(long long v)
  // GMP++ doesn't have a long long constructor for some reason, so
  // instead of creating the instance in one call, create an mpz for
  // the high word, shift it, then add the low word.
  : impl(std::shared_ptr<void>(
           new mpz_class(
             (mpz_class(static_cast<long>(v >> 32)) << 32)
             + mpz_class(static_cast<long>(v & 0xffffffff))
           )
         ))
{
}

sf::mpz::operator std::string() const {
  return static_cast<mpz_class*>(impl.get())->get_str();
}
