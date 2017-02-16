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
#include "utility/inc/StringUtils.hpp"
#include "utility/inc/DateEntity.h"

namespace cbtek {
namespace common {
namespace utility {
namespace DateUtils {

static inline std::string toShortDateString(const DateEntity &date,
                                            const std::string &format="mm-dd-yyyy")
{
    std::string dateStr=format;

    if (StringUtils::contains(dateStr,"yyyy"))
    {
        dateStr=StringUtils::replace(dateStr,"yyyy",StringUtils::toString(date.getYear()));
    }

    if(StringUtils::contains(dateStr,"mm"))
    {
        dateStr=StringUtils::replace(dateStr,"mm",(date.getMonth()<10?"0"+StringUtils::toString(date.getMonth()):StringUtils::toString(date.getMonth())));
    }

    if(StringUtils::contains(dateStr,"dd"))
    {
        dateStr=StringUtils::replace(dateStr,"dd",(date.getDay()<10?"0"+StringUtils::toString(date.getDay()):StringUtils::toString(date.getDay())));
    }
    return dateStr;
}

static inline std::string toLongDateString(const DateEntity &date)
{
    std::string months[12] =
    {
        "January","February","March","April",
        "May","June","July","August",
        "September","October","November","December"
    };

    if (date.getMonth() <13)
    {
        return months[date.getMonth()-1]+" "+StringUtils::toString(date.getDay())+", "+StringUtils::toString(date.getYear());
    }
    return "";
}

static inline DateEntity getCurrentDate()
{
    time_t t = time(0);
    struct tm * now = localtime( & t );
    return DateEntity(now->tm_mon + 1,now->tm_mday,now->tm_year + 1900);
}

}}}}//namespace
