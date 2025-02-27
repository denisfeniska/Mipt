#include "rational.h"
#include <numeric>

Rational::Rational(int number) : numerator_(number), denominator_(1) {} // NOLINT

void Rational::Reduction() {
  int gcd = std::gcd(numerator_, denominator_);
  numerator_ /= gcd;
  denominator_ /= gcd;
  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int number) {
  numerator_ = number;
  Reduction();
}

void Rational::SetDenominator(int number) {
  if (number == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = number;
  Reduction();
}

Rational Rational::operator+(const Rational& second) const {
  Rational res;
  res.numerator_ = numerator_ * second.denominator_ + second.numerator_ * denominator_;
  res.denominator_ = denominator_ * second.denominator_;
  res.Reduction();
  return res;
}

Rational Rational::operator-(const Rational& second) const {
  Rational res;
  res.numerator_ = numerator_ * second.denominator_ - second.numerator_ * denominator_;
  res.denominator_ = denominator_ * second.denominator_;
  res.Reduction();
  return res;
}

Rational Rational::operator*(const Rational& second) const {
  Rational res;
  res.numerator_ = numerator_ * second.numerator_;
  res.denominator_ = denominator_ * second.denominator_;
  res.Reduction();
  return res;
}

Rational Rational::operator/(const Rational& second) const {
  if (second.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }
  Rational res;
  res.numerator_ = numerator_ * second.denominator_;
  res.denominator_ = denominator_ * second.numerator_;
  res.Reduction();
  return res;
}

Rational& Rational::operator+=(const Rational& second) {
  numerator_ = numerator_ * second.denominator_ + second.numerator_ * denominator_;
  denominator_ = denominator_ * second.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator-=(const Rational& second) {
  numerator_ = numerator_ * second.denominator_ - second.numerator_ * denominator_;
  denominator_ = denominator_ * second.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator*=(const Rational& second) {
  numerator_ = numerator_ * second.numerator_;
  denominator_ = denominator_ * second.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator/=(const Rational& second) {
  if (second.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }
  numerator_ = numerator_ * second.denominator_;
  denominator_ = denominator_ * second.numerator_;
  Reduction();
  return *this;
}

Rational Rational::operator+() const {
  return {numerator_, denominator_};
}

Rational Rational::operator-() const {
  return {-numerator_, denominator_};
}

Rational& Rational::operator++() {
  numerator_ = numerator_ + denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator--() {
  numerator_ = numerator_ - denominator_;
  Reduction();
  return *this;
}

Rational Rational::operator++(int) {
  Rational first = *this;
  numerator_ = numerator_ + denominator_;
  Reduction();
  return first;
}

Rational Rational::operator--(int) {
  Rational first = *this;
  numerator_ = numerator_ - denominator_;
  Reduction();
  return first;
}

bool Rational::operator==(const Rational& second) const {
  return numerator_ == second.numerator_ && denominator_ == second.denominator_;
}

bool Rational::operator!=(const Rational& second) const {
  return !(*this == second);
}

bool Rational::operator<(const Rational& second) const {
  return numerator_ * second.denominator_ < second.numerator_ * denominator_;
}

bool Rational::operator>(const Rational& second) const {
  return second < *this;
}

bool Rational::operator<=(const Rational& second) const {
  return !(second < *this);
}

bool Rational::operator>=(const Rational& second) const {
  return !(*this < second);
}

bool operator==(const Rational& rational, int number) {
  return rational == Rational(number);
}

bool operator!=(const Rational& rational, int number) {
  return rational != Rational(number);
}

bool operator<(const Rational& rational, int number) {
  return rational < Rational(number);
}

bool operator<=(const Rational& rational, int number) {
  return rational <= Rational(number);
}

bool operator>(const Rational& rational, int number) {
  return rational > Rational(number);
}

bool operator>=(const Rational& rational, int number) {
  return rational >= Rational(number);
}

bool operator==(int number, const Rational& rational) {
  return Rational(number) == rational;
}

bool operator!=(int number, const Rational& rational) {
  return Rational(number) != rational;
}

bool operator<(int number, const Rational& rational) {
  return Rational(number) < rational;
}

bool operator<=(int number, const Rational& rational) {
  return Rational(number) <= rational;
}

bool operator>(int number, const Rational& rational) {
  return Rational(number) > rational;
}

bool operator>=(int number, const Rational& rational) {
  return Rational(number) >= rational;
}

std::ostream& operator<<(std::ostream& cout, const Rational& rational) {
  cout << rational.numerator_;
  if (rational.denominator_ != 1) {
    cout << "/" << rational.denominator_;
  }
  return cout;
}

std::istream& operator>>(std::istream& cin, Rational& rational) {
  int numerator = 0;
  int denominator = 1;
  char elem = '0';
  cin >> numerator;
  if (cin.peek() == '/') {
    cin >> elem;
    cin >> denominator;
  }
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  rational = Rational(numerator, denominator);
  return cin;
}