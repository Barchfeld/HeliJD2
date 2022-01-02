#ifndef JD_HPP_INCLUDED
#define JD_HPP_INCLUDED

#include <cmath>
#include <ctime>
#include <chrono>
#include <string>

struct datetime {
    long double jd;
    std::tm     gregorian;

    datetime() : jd(0.0), gregorian({ 0 }) {};
} ;

long double jd( int year, int month, int day, int utc_hour, int utc_minute, double utc_second);

long double jd( std::string isoDate);

struct datetime jd2gregor( long double jd);

struct datetime jdFromDateTime(struct datetime dt);

#endif // JD_HPP_INCLUDED
