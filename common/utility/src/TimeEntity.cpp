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

#include "TimeEntity.h"
#include "utility/inc/StringUtils.hpp"

namespace cbtek {
namespace common {
namespace utility {

TimeEntity::TimeEntity(const size_t &time)
{

    std::string timeStr=StringUtils::toString(time);
    if (timeStr.size()==6)
    {
        m_hour=StringUtils::toNumber<size_t>(timeStr.substr(0,2));
        m_minute=StringUtils::toNumber<size_t>(timeStr.substr(2,2));
        m_second=StringUtils::toNumber<size_t>(timeStr.substr(4,2));
    }
    else if (timeStr.size()==5)
    {
        m_hour=StringUtils::toNumber<size_t>(timeStr.substr(0,1));
        m_minute=StringUtils::toNumber<size_t>(timeStr.substr(1,2));
        m_second=StringUtils::toNumber<size_t>(timeStr.substr(3,2));
    }
    else
    {
        m_hour=0;
        m_minute=0;
        m_second=0;

    }
    m_millisecond=0;
}

TimeEntity::TimeEntity()
{
    m_hour=0;
    m_minute=0;
    m_second=0;
    m_millisecond=0;
}

TimeEntity::TimeEntity(size_t hour,
                       size_t minute,
                       size_t second,
                       size_t millisecond)
{
    m_hour=hour;
    m_minute=minute;
    m_second=second;
    m_millisecond=millisecond;
}

bool TimeEntity::operator>(const TimeEntity &time) const
{
    return (this->getAsSeconds() > time.getAsSeconds());
}

bool TimeEntity::operator<(const TimeEntity &time) const
{
    return (this->getAsSeconds() < time.getAsSeconds());
}

bool TimeEntity::operator<=(const TimeEntity &time) const
{
    return (this->getAsSeconds() <= time.getAsSeconds());
}

bool TimeEntity::operator>=(const TimeEntity &time) const
{
    return (this->getAsSeconds() >= time.getAsSeconds());
}

bool TimeEntity::operator==(const TimeEntity &time) const
{
    return (time.getHour()==m_hour && time.getMinute()==m_minute && time.getSecond()==m_second && time.getMillisecond()==m_millisecond);
}

void TimeEntity::setHour(const size_t &hour)
{
    m_hour=hour;
}

void TimeEntity::setMinute(const size_t &minute)
{
    m_minute=minute;
}

void TimeEntity::setSecond(const size_t &second)
{
    m_second=second;
}

void TimeEntity::setMillisecond(const size_t &millisecond)
{
    m_millisecond=millisecond;
}

size_t TimeEntity::getHour() const
{
    return m_hour;
}

size_t TimeEntity::getMinute() const
{
    return m_minute;
}

size_t TimeEntity::getSecond() const
{
    return m_second;
}

size_t TimeEntity::getMillisecond() const
{
    return m_millisecond;
}

size_t TimeEntity::toTimeInteger() const
{
    std::string hourStr=StringUtils::toString(m_hour);
    std::string minStr=StringUtils::toString(m_minute);
    std::string secStr=StringUtils::toString(m_second);
    std::string timeStr=(m_hour<10?"0"+hourStr:hourStr) + (m_minute<10?"0"+minStr:minStr) + (m_second<10?"0"+secStr:secStr);
    return StringUtils::toNumber<size_t>(timeStr);
}

size_t TimeEntity::getAsMinutes() const
{
    return (m_hour*60)+m_minute;
}

size_t TimeEntity::getAsSeconds() const
{
    return (getAsMinutes()*60)+m_second;
}

size_t TimeEntity::getAsMilliseconds() const
{
    return (getAsSeconds()*1000)+m_millisecond;
}

size_t TimeEntity::getAsMicroseconds() const
{
    return (getAsMilliseconds()*1000);
}
}}}//namespace
