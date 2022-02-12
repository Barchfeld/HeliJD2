#include "DeltaT.h"

#include <cmath>
#include <string>
#include <boost/algorithm/string.hpp>



// 
// https://eclipse.gsfc.nasa.gov/SEcat5/deltatpoly.html
//
// We define the decimal year "y" as follows :
//     y = year + (month - 0.5) / 12
//
// Between years 1900 and 1920, calculate:
//
// ΔT = -2.79 + 1.494119 * t - 0.0598939 * t ^ 2 + 0.0061966 * t ^ 3 - 0.000197 * t ^ 4
// where: t = y - 1900
//
// Between years 1920 and 1941, calculate :
//
//	ΔT = 21.20 + 0.84493 * t - 0.076100 * t ^ 2 + 0.0020936 * t ^ 3
//	where : t = y - 1920
//
//	Between years 1941 and 1961, calculate :
//
//	ΔT = 29.07 + 0.407 * t - t ^ 2 / 233 + t ^ 3 / 2547
//	where : t = y - 1950
//
//	Between years 1961 and 1986, calculate :
//
//	ΔT = 45.45 + 1.067 * t - t ^ 2 / 260 - t ^ 3 / 718
//	where : t = y - 1975
//
//	Between years 1986 and 2005, calculate :
//
//	ΔT = 63.86 + 0.3345 * t - 0.060374 * t ^ 2 + 0.0017275 * t ^ 3 + 0.000651814 * t ^ 4
//	+ 0.00002373599 * t ^ 5
//	where : t = y - 2000
//
//	Between years 2005 and 2050, calculate :
//
//	ΔT = 62.92 + 0.32217 * t + 0.005589 * t ^ 2
//	where : t = y - 2000

double getDeltaT(int const year, int const month)
{
	double t{ 25.0 };
	double deltaT{ 70.0 };
	double y = year + (month - 0.5) / 12.;

	if ( (y < 1900) || (y > 2049))
	{
		throw 9998;
	}

	if ((y >= 1900) && (y < 1920))
	{
		throw 9997;
	}

	if ((y >= 1920) && (y < 1941))
	{
		throw 9996;
	}

	if ((y >= 1941) && (y < 1961))
	{
		t = y - 1950.0;
		deltaT = 29.07 + 0.407 * t - t*t / 233 + t*t*t / 2547;
	}

	if ((y >= 1961) && (y < 1986))
	{
		t = y - 1975.0;
		deltaT = 45.45 + 1.067 * t - t * t / 260 - t * t * t / 718;
	}

	if ((y >= 1986) && (y < 2005))
	{
		t = y - 2000.0;
		deltaT = 63.86 + 0.3345 * t - 0.060374 * t * t + 0.0017275 * pow(t, 3) + 
			0.000651814 * pow(t, 4) + 0.00002373599 * pow(t, 5);
	}

	if ((y >= 2005) && (y < 2050))
	{
		t = y - 2000.0;
		deltaT = 62.92 + 0.32217 * t + 0.005589 * t*t;
	}


	return deltaT;
}

double getDeltaT(std::string isoDateString)
{

	boost::algorithm::trim(isoDateString);
	std::string yearStr{};
	std::string monthStr{};
	std::string::size_type sz;

	yearStr = isoDateString.substr(0, 4);
	monthStr = isoDateString.substr(5, 2);
	int const year = std::stoi(yearStr, &sz);
	int const month = std::stoi(monthStr, &sz);
	return getDeltaT(year, month);
}

