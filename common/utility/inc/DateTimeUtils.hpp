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
#ifndef _CBTEK_COMMON_UTILITY_DATETIMEUTILS_HPP_
#define _CBTEK_COMMON_UTILITY_DATETIMEUTILS_HPP_

#include "TimeUtils.hpp"
#include "DateUtils.hpp"
#include "StringUtils.hpp"

namespace cbtek{
namespace common{
namespace utility{
namespace DateTimeUtils{

inline std::string getDisplayTimeStamp()
{
    return (DateUtils::toShortDateString(DateUtils::getCurrentDate(),"mm/dd/yyyy")+" at "+StringUtils::toString(TimeUtils::to12HourTimeString(TimeUtils::getCurrentTime())));
}

inline std::string getTimeStamp()
{
    return (DateUtils::toShortDateString(DateUtils::getCurrentDate(),"yyyymmdd")+"T"+StringUtils::toString(TimeUtils::getCurrentTime().toTimeInteger())+"."+StringUtils::toString((std::uint64_t)TimeUtils::getMillisecondsNow()));
}

}}}} //namespace
#endif //_CBTEK_COMMON_UTILITY_DATETIMEUTILS_HPP_
