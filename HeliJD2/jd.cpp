
#include <exception>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "jd.h"


long double jd( int year, int month, int day, int utc_hour, int utc_minute, double utc_second)
{
    if ( (year < 1901) || (year > 2099) ) {
        throw 9999;
    }

    long double jd{0.0};
    long double t1 = utc_minute + utc_second / 60.0;
    long double t2 = utc_hour + t1 / 60.0;
    long double utc_day = day + t2 / 24.0;

    jd = 367 * year;
    long t3 = static_cast<int>( (month + 9)/12 );
    long t4 = static_cast<int>( ( 7 * (year + t3)/4) );
    jd -= t4;
    jd += static_cast<int>( 275 * month / 9 );
    jd += utc_day;
    jd += 1721013.5;

    return jd;
}


long double jd( std::string isoDate) {
    std::tm tp {};
    std::stringstream ss;
    ss << isoDate;
    ss >> std::get_time(&tp, "%Y-%m-%dT%H:%M:%S");
    if (ss.fail()) {
        std::cout << "ISO-Date-Parse failed\n";
        std::exit(1);
    }
    return jd(tp.tm_year + 1900,tp.tm_mon + 1, tp.tm_mday,tp.tm_hour,
              tp.tm_min, static_cast<double>(tp.tm_sec) );
}


struct datetime jdFromDateTime(struct datetime dt) {
    dt.jd =  jd(dt.gregorian.tm_year, dt.gregorian.tm_mon, dt.gregorian.tm_mday,
                dt.gregorian.tm_hour, dt.gregorian.tm_min,
                static_cast<double>(dt.gregorian.tm_sec));
    return dt;
}


struct datetime jd2gregor( long double jd) {
    if ((jd < 2415079.5) || (jd > 2488128.49)) {
        throw 9998;
    }

    struct datetime tempTime {};
    tempTime.jd = jd;
    long double mjd = jd - 2400000.5;
    long double HH;
    long double MM;
    long double SEC;

    long a, b, c, d, e, f;
    double fractionOfDay;
    a = long(mjd + 2400001.0);
    b = long((a - 1867216.25) / 36524.25);
    c = a + b - (b/4) + 1525;
    d = long((c - 122.1)/365.25);
    e = 365 * d + d/4;
    f = long((c-e)/30.6001);

    tempTime.gregorian.tm_mday = c - e - int(30.6001 * f);
    tempTime.gregorian.tm_mon = f - 1 - 12 * (f/14);
    tempTime.gregorian.tm_year = d - 4715 - ((7 + tempTime.gregorian.tm_mon) / 10 );
    fractionOfDay = mjd - floorl(mjd);
    HH = 24.0 * fractionOfDay;
    tempTime.gregorian.tm_hour = static_cast<int>(HH);
    MM = (HH - tempTime.gregorian.tm_hour) * 60.0;
    tempTime.gregorian.tm_min = static_cast<int>(MM);
    SEC = (MM - tempTime.gregorian.tm_min) * 60.0;
    tempTime.gregorian.tm_sec = static_cast<int>(SEC);

    return tempTime;
}
