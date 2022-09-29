#include "Math.h"

namespace math {
	namespace functions {
		constexpr types::Integer gcd(types::Integer a, types::Integer b) {
			const types::Integer sign = a * b >= 0 ? 1 : -1;
			while (b) {
				const types::Integer ta = a;
				a = b;
				b = ta % a;
			}
			return abs(a) * sign;
		}

		constexpr types::Integer lcm(const types::Integer a, const types::Integer b) {
			return a * b / gcd(a, b);
		}
	}
}