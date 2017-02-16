/**
MIT License

Copyright (c) 2016 cbtek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef _CBTEK_COMMON_UTILITY_TIME_UTILS_HPP_
#define _CBTEK_COMMON_UTILITY_TIME_UTILS_HPP_

#include "utility/inc/TimeEntity.h"

#include <chrono>
#include <ctime>
#include <sstream>

namespace cbtek {
namespace common {
namespace utility {

typedef std::chrono::system_clock SystemClock;
typedef std::chrono::high_resolution_clock HighResolutionClock;
typedef HighResolutionClock::time_point HighResolutionTimePoint;
typedef SystemClock::time_point SystemTimePoint;
typedef std::chrono::milliseconds Milliseconds;
typedef std::chrono::microseconds Microseconds;
typedef std::chrono::nanoseconds Nanoseconds;
typedef std::chrono::seconds Seconds;

namespace TimeUtils {

template <typename T>
static inline std::string toString(T value)
{
    std::ostringstream out;
    out << value;
    return out.str();
}

static inline uint64_t getSecondsNow()
{
    return time(NULL);
}

static inline double getNanosecondsNow()
{
    HighResolutionTimePoint tp = HighResolutionClock::now();
    Seconds secs= std::chrono::duration_cast<Seconds>(tp.time_since_epoch());
    return secs.count();
}

static inline double getMicrosecondsNow()
{
    HighResolutionTimePoint tp = HighResolutionClock::now();
    Microseconds secs= std::chrono::duration_cast<Microseconds>(tp.time_since_epoch());
    return secs.count();
}

static inline double getMillisecondsNow()
{
    HighResolutionTimePoint tp = HighResolutionClock::now();
    Milliseconds secs= std::chrono::duration_cast<Milliseconds>(tp.time_since_epoch());
    return secs.count();
}

static inline std::string toTimeString(const TimeEntity &time)
{
    return (time.getHour()<10?"0":"")+toString(time.getHour())+":"+(time.getMinute()<10?"0":"")+toString(time.getMinute())+":"+(time.getSecond()<10?"0":"")+toString(time.getSecond());
}

static inline std::string to12HourTimeString(const TimeEntity &time)
{
    std::string extension="AM";
    size_t hour=time.getHour();
    if (time.getHour()>11 )
    {
        extension="PM";
        if (time.getHour()!=12)
        {
            hour=time.getHour()-12;
        }
    }

    if (hour==0)
    {
        hour=12;
    }

    return (hour<10?"0":"")+toString(hour)+":"+(time.getMinute()<10?"0":"")+toString(time.getMinute())+":"+(time.getSecond()<10?"0":"")+toString(time.getSecond())+ " "+extension;
}


static inline TimeEntity getCurrentTime()
{
    time_t t = time(0);
    struct tm * now = localtime( & t );
    return TimeEntity(now->tm_hour,now->tm_min,now->tm_sec);
}

static inline TimeEntity getTimeFromSeconds(const uint64_t &secs)
{
    TimeEntity tm;
    tm.setHour(secs/3600);
    tm.setMinute((secs%3600)/60);
    tm.setSecond((secs%3600)%60);
    return tm;
}

static inline TimeEntity getTimeFromMilliseconds(const uint64_t &ms)
{
    return getTimeFromSeconds(ms/1000);
}

}}}}//namespace

#endif
