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
#ifndef _CBTEK_COMMON_UTILITY_DATEENTITY_H
#define _CBTEK_COMMON_UTILITY_DATEENTITY_H

#include <cstdlib>
#include <string>

namespace cbtek {
namespace common {
namespace utility {
class DateEntity
{

public:
    DateEntity();

    DateEntity(const size_t & month, const size_t & day, const size_t & year);

    DateEntity(const size_t & dateInteger);

    size_t getMonth() const;

    size_t getDay() const;

    size_t getYear() const;

    void setMonth(const size_t & month);

    void setDay(const size_t & day);

    void setYear(const size_t & year);

    size_t toDateInteger() const;

    bool operator<(const DateEntity & date) const;

    bool operator<=(const DateEntity & date) const;

    bool operator>(const DateEntity & date) const;

    bool operator>=(const DateEntity & date) const;

    bool operator==(const DateEntity & date) const;

    bool operator!=(const DateEntity & date) const;

    size_t operator-(const DateEntity& date)const;

    bool isLeapYear() const;

    size_t getDays() const;
private:   
    size_t m_month,m_day,m_year;

};
}}}//namespace
#endif // _CBTEK_COMMON_UTILITY_DATEENTITY_H
