#pragma once

#include <ostream>
#undef INFINITY	//INFINITY is a macro in the std namespace that will interfere with Fraction::INFINITY and other constants

namespace math {
	namespace types {
		// Util macro
		#define MAKE_BINARY_OP(type, op) \
		type operator##op(const type& b) const {\
			type result = *this;\
			result op##= b;\
			return result;\
		}\
		type& operator##op##=(const type&);
		
		
		typedef long long int Integer;
		typedef double Number;

		class Fraction {
			Integer numerator, denominator;
		public:
			const static Fraction INFINITY;
			const static Fraction UNDEFINED;
			const static Fraction ZERO;

			Fraction() : Fraction(1) {}
			Fraction(const Integer n) : numerator(n), denominator(1) {}
			Fraction(const Integer n, const Integer d) : numerator(n), denominator(d) {simplify();}

			constexpr void simplify();

			constexpr Number toNumber() const;

			constexpr bool isIntegral() const;

			constexpr operator Number() const;
			constexpr operator Integer() const;

			Integer getNumerator() const {return numerator;}
			Integer getDenominator() const {return denominator;}

			bool operator==(const Fraction&) const;
			
			Fraction operator-() const;
			
			MAKE_BINARY_OP(Fraction, *)
			MAKE_BINARY_OP(Fraction, /)
			MAKE_BINARY_OP(Fraction, +)
			MAKE_BINARY_OP(Fraction, -)
		};

		std::ostream& operator<<(std::ostream&, const Fraction&);
		
		#undef MAKE_BINARY_OP
	}

	namespace functions {
		constexpr types::Integer gcd(types::Integer, types::Integer);
		constexpr types::Integer lcm(types::Integer, types::Integer);

		types::Fraction gcd(const types::Fraction&, const types::Fraction&);
		types::Fraction lcm(const types::Fraction&, const types::Fraction&);
	}
}