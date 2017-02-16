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

#ifndef _CBTEK_COMMON_UTILITY_TIME_ENTITY_HPP_
#define _CBTEK_COMMON_UTILITY_TIME_ENTITY_HPP_

#include <cstdlib>
#include <string>

#include "UtilityCommon.hpp"

namespace cbtek {
namespace common {
namespace utility {

class CBTEK_UTILS_DLL TimeEntity
{
public:

    /**
     * @brief TimeEntity
     * @param time
     */
    TimeEntity (const size_t  & time);

    /**
     * @brief TimeEntity
     */
    TimeEntity();

    /**
     * @brief TimeEntity
     * @param hour
     * @param minute
     * @param second
     * @param millisecond
     */
    TimeEntity(size_t hour,
               size_t minute,
               size_t second,
               size_t millisecond=0);

    /**
     * @brief setHour
     * @param hour
     */
    void setHour(const size_t & hour);

    /**
     * @brief setMinute
     * @param minute
     */
    void setMinute(const size_t & minute);

    /**
     * @brief setSecond
     * @param second
     */
    void setSecond(const size_t & second);

    /**
     * @brief setMillisecond
     * @param millisecond
     */
    void setMillisecond(const size_t & millisecond);

    /**
     * @brief operator >
     * @param time
     * @return
     */
    bool operator>(const TimeEntity &time) const;

    /**
     * @brief operator <
     * @param time
     * @return
     */
    bool operator<(const TimeEntity &time) const;

    /**
     * @brief operator <=
     * @param time
     * @return
     */
    bool operator<=(const TimeEntity &time) const;

    /**
     * @brief operator >=
     * @param time
     * @return
     */
    bool operator>=(const TimeEntity &time) const;

    /**
     * @brief operator ==
     * @param time
     * @return
     */
    bool operator==(const TimeEntity &time) const;

    /**
     * @brief getHour
     * @return
     */
    size_t getHour() const;

    /**
     * @brief getMinute
     * @return
     */
    size_t getMinute() const;

    /**
     * @brief getSecond
     * @return
     */
    size_t getSecond() const;

    /**
     * @brief getMillisecond
     * @return
     */
    size_t getMillisecond() const;

    /**
     * @brief toTimeInteger
     * @return
     */
    size_t toTimeInteger() const;

    /**
     * @brief getAsMinutes
     * @return
     */
    size_t getAsMinutes() const;

    /**
     * @brief getAsSeconds
     * @return
     */
    size_t getAsSeconds() const;

    /**
     * @brief getAsMilliseconds
     * @return
     */
    size_t getAsMilliseconds() const;

    /**
     * @brief getAsMicroseconds
     * @return
     */
    size_t getAsMicroseconds() const;


private:
    size_t m_hour;
    size_t m_minute;
    size_t m_second;
    size_t m_millisecond;
};
}}}//namespace
#endif // _CBTEK_COMMON_UTILITY_TIME_ENTITY_HPP_
