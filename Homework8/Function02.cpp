#include "Function02.h"

namespace fre {
	double F1::Value(double x) { return x * x - 2; }
	double F1::Deriv(double x) { return 2 * x; }

	double F2::Value(double x) { return x * x - a; }
	double F2::Deriv(double x) { return 2 * x; }
}