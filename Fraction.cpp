#include "Math.h"

namespace math {
	namespace types {
		const Fraction Fraction::INFINITY {1, 0};
		const Fraction Fraction::UNDEFINED {0, 0};
		const Fraction Fraction::ZERO {0, 1};
		
		void Fraction::simplify() {
			if (numerator != 0) {
				if (denominator != 0) {
					const Integer gcd = functions::gcd(numerator, denominator);
					numerator /= gcd;
					denominator /= gcd;
				}
				else { // simplify N/0 to 1/0 or -1/0 depending on the sign
					numerator = numerator > 0 ? 1 : -1;
				}
			}
			else if (denominator != 0) { // simplify 0/N to 0/1 (ignoring sign)
				denominator = 1;
			}
			
			// 0/0 is unchanged
		}
		
		Fraction& Fraction::operator*=(const Fraction& b) {
			numerator *= b.numerator;
			denominator *= b.denominator;
			simplify();
			return *this;
		}

		Fraction& Fraction::operator/=(const Fraction& b) {
			numerator *= b.denominator;
			denominator *= b.numerator;
			simplify();
			return *this;
		}

		Fraction& Fraction::operator+=(const Fraction& b) {
			const Integer d = functions::lcm(denominator, b.denominator);
			numerator = numerator * d / denominator + b.numerator * d / b.denominator;
			denominator = d;
			simplify();
			return *this;
		}

		Fraction& Fraction::operator-=(const Fraction& b) {
			const Integer d = functions::lcm(denominator, b.denominator);
			numerator = numerator * d / denominator - b.numerator * d / b.denominator;
			denominator = d;
			simplify();
			
			return *this;
		}

		Fraction Fraction::operator-() const {
			return {-numerator, denominator};
		}

		Number Fraction::toNumber() const {
			return static_cast<double>(numerator) / static_cast<double>(denominator);
		}

		bool Fraction::isIntegral() const {
			return denominator == 1;
		}

		Fraction::operator Number() const {
			return toNumber();
		}

		Fraction::operator Integer() const
		{
			if (!isIntegral()) throw std::exception("Could not convert fraction to integer");
			return numerator;
		}

		bool Fraction::operator==(const Fraction& f) const {
			return numerator == f.numerator && denominator == f.denominator;
		}

		std::ostream& operator<<(std::ostream& os, const Fraction& f) {
			if(f == Fraction::UNDEFINED) {
				os << "NaN";
			}
			if(f == Fraction::INFINITY) {
				os << "Infinity";
			}
			else if (f == -Fraction::INFINITY) {
				os << "-Infinity";
			}
			else if (f.getDenominator() == 1) {
				os << f.getNumerator();
			}
			else {
				os << f.getNumerator() << "/" << f.getDenominator();
			}
			
			return os;
		}
	}

	namespace functions {
		types::Fraction gcd(const types::Fraction& a, const types::Fraction& b) {
			return {gcd(a.getNumerator(), b.getNumerator()), lcm(a.getDenominator(), b.getDenominator())};
		}

		types::Fraction lcm(const types::Fraction& a, const types::Fraction& b) {
			return {lcm(a.getNumerator(), b.getNumerator()), gcd(a.getDenominator(), b.getDenominator())};
		}
	}
}
