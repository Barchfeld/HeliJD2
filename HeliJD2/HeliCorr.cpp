

#define _USE_MATH_DEFINES
#include <cmath>
#include "HeliCorr.h"
#include "VarStar.h"

long double norm(long double value)
{
	while (value > 360.0)
	{
		value -= 360.0;
	}
	while (value < -360.0 )
	{
		value += 360.0;
	}
	return value;
}


long double heliCorr(const long double jd_ut, const VarStar& star)
{
	long double corr{0.0};
	const long double dtor = M_PI / 180.0;

	long double n = jd_ut - 2451545.0;
	long double L = norm(280.460 + 0.9856474 * n);
	long double g = norm(357.528 + 0.9856003 * n);
	long double l = norm(L + 1.915 * sin(g * dtor) + 0.020 * sin(2 * g * dtor));
	long double R = 1.00014 - 0.01671 * cos(g * dtor) - 0.00014 * cos(2 * g * dtor);
	long double eps = 23.439 - 0.0000004 * n;

	long double part1 = (R * cos(l * dtor)) * 
		( cos(star.getRectDeg() * dtor) * cos(star.getDeclDeg() * dtor) );

	long double part2 = (R * sin(l * dtor)) * 
		(sin(eps * dtor) * sin(star.getDeclDeg() * dtor) + 
		cos(eps * dtor) * cos(star.getDeclDeg() * dtor) * sin(star.getRectDeg() * dtor));

	corr = -0.0057755 * (part1 + part2);

	return corr;
}
