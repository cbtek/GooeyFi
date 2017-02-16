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
#include "DateEntity.h"

#include "utility/inc/StringUtils.hpp"

namespace cbtek {
namespace common {
namespace utility {

DateEntity::DateEntity()
{
    m_month=1;
    m_day=1;
    m_year=1970;
}

DateEntity::DateEntity(const size_t &month, const size_t &day, const size_t &year)
{
    m_month=month;
    m_day=day;
    m_year=year;
}

DateEntity::DateEntity(const size_t &dateInteger)
{
    std::string dateStr=StringUtils::toString(dateInteger);
    if (dateStr.size()==8)
    {
        m_year=StringUtils::toNumber<size_t>(dateStr.substr(0,4));
        m_month=StringUtils::toNumber<size_t>(dateStr.substr(4,2));
        m_day=StringUtils::toNumber<size_t>(dateStr.substr(6,2));
    }   
    else
    {
        m_month=1;
        m_day=1;
        m_year=1970;
    }
}

size_t DateEntity::getMonth() const
{
    return m_month;
}

size_t DateEntity::getDay() const
{
    return m_day;
}

size_t DateEntity::getYear() const
{
    return m_year;
}

void DateEntity::setMonth(const size_t &month)
{
    m_month=month;
}

void DateEntity::setDay(const size_t &day)
{
    m_day=day;
}

void DateEntity::setYear(const size_t &year)
{
    m_year=year;
}

size_t DateEntity::toDateInteger() const
{
    std::string dateStr=StringUtils::toString(m_year)+
            (m_month<10?"0"+StringUtils::toString(m_month):StringUtils::toString(m_month))+
            (m_day<10?"0"+StringUtils::toString(m_day):StringUtils::toString(m_day));
    return StringUtils::toNumber<size_t>(dateStr);
}

bool DateEntity::operator <(const DateEntity &date) const
{
   return toDateInteger() < date.toDateInteger();
}

bool DateEntity::operator <=(const DateEntity &date) const
{
    return toDateInteger() <= date.toDateInteger();
}

bool DateEntity::operator >(const DateEntity &date) const
{
    return toDateInteger()>date.toDateInteger();
}

bool DateEntity::operator >=(const DateEntity &date) const
{
    return toDateInteger()>=date.toDateInteger();
}

bool DateEntity::operator ==(const DateEntity &date) const
{
    return toDateInteger()==date.toDateInteger();
}

bool DateEntity::operator !=(const DateEntity &date) const
{
    return toDateInteger()!=date.toDateInteger();
}

size_t DateEntity::operator -(const DateEntity &date) const
{

    size_t lowYear=0,highYear=0;
    size_t days = 0;
    if (m_year<date.getYear())
    {
        lowYear=m_year;
        highYear=date.getYear();
    }

    else if (m_year>date.getYear())
    {
        lowYear=date.getYear();
        highYear=m_year;
    }

    for (size_t a1 = lowYear;a1<highYear;++a1)
    {
        days+=365;
        if (DateEntity(1,1,a1).isLeapYear())
        {
            days++;
        }
    }
    DateEntity d1(date.getMonth(),date.getDay(),1901);
    DateEntity d2(getMonth(),getDay(),1901);
    size_t d1Days = d1.getDays();
    size_t d2Days = d2.getDays();
    if (d1Days>d2Days)
    {
        days += d1Days-d2Days;
    }
    else
    {
        days += d2Days-d1Days;
    }

    return days;
}

bool DateEntity::isLeapYear() const
{
//    The year is evenly divisible by 4;
//    If the year can be evenly divided by 100, it is NOT a leap year, unless;
//    The year is also evenly divisible by 400. Then it is a leap year.
    return ((m_year % 4 == 0 && m_year % 100 != 0) || m_year % 400 == 0);
}

size_t DateEntity::getDays() const
{
    size_t daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    size_t days=0;
    for (size_t a1 = 0;a1<m_month-1;++a1)
    {
        if (a1 < 12)
        {
            if(a1==1 && isLeapYear())
            {
                days+=daysInMonth[a1]+1;
            }
            else
            {
                days+=daysInMonth[a1];
            }

        }

    }
    return days+(m_day);
}

}}}//namespace
