#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <algorithm>

class RationalDivisionByZero {};

class Rational {
 public:
  Rational() : numerator_(0), denominator_(1) {}

  Rational(int number); // NOLINT

  Rational(int number1, int number2) : numerator_(number1), denominator_(number2) {
    if (denominator_ == 0) {
      throw RationalDivisionByZero{};
    }
    Reduction();
  }

  int GetNumerator() const;

  int GetDenominator() const;

  void SetNumerator(int number);

  void SetDenominator(int number);

  Rational operator+(const Rational& second) const;

  Rational operator-(const Rational& second) const;

  Rational operator*(const Rational& second) const;

  Rational operator/(const Rational& second) const;

  Rational& operator+=(const Rational& second);

  Rational& operator-=(const Rational& second);

  Rational& operator*=(const Rational& second);

  Rational& operator/=(const Rational& second);

  Rational operator+() const;

  Rational operator-() const;

  Rational& operator++();

  Rational& operator--();

  Rational operator++(int);

  Rational operator--(int);

  bool operator==(const Rational& second) const;

  bool operator!=(const Rational& second) const;

  bool operator<(const Rational& second) const;

  bool operator>(const Rational& second) const;

  bool operator<=(const Rational& second) const;

  bool operator>=(const Rational& second) const;

  friend bool operator==(const Rational& rational, int number);

  friend bool operator!=(const Rational& rational, int number);

  friend bool operator<(const Rational& rational, int number);

  friend bool operator<=(const Rational& rational, int number);

  friend bool operator>(const Rational& rational, int number);

  friend bool operator>=(const Rational& rational, int number);

  friend bool operator==(int number, const Rational& rational);

  friend bool operator!=(int number, const Rational& rational);

  friend bool operator<(int number, const Rational& rational);

  friend bool operator<=(int number, const Rational& rational);

  friend bool operator>(int number, const Rational& rational);

  friend bool operator>=(int number, const Rational& rational);

  friend std::ostream& operator<<(std::ostream& cout, const Rational& rational);

  friend std::istream& operator>>(std::istream& cin, Rational& rational);

 private:
  int numerator_;
  int denominator_;

  void Reduction();
};

#endif