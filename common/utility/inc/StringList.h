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

#ifndef _CBTEK_COMMON_UTILITY_STRINGLIST_H_
#define _CBTEK_COMMON_UTILITY_STRINGLIST_H_

#include <vector>
#include <string>
#include <list>
#include <sstream>
#include <map>

#include "UtilityCommon.hpp"

namespace cbtek {
namespace common {
namespace utility {

typedef std::vector<std::string> StringVector;
typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
typedef CoutType& (*OutFunc)(CoutType&);

class CBTEK_UTILS_DLL StringList : public std::vector<std::string>
{
public:

    static size_t npos;

    typedef StringList::iterator StringListIter;

    typedef StringList::const_iterator StringListConstIter;

    StringList();

    StringList(const std::string &);

    StringList(const std::vector<std::string> &);

    StringList(const std::list<std::string> & strList);

    StringList & operator<<(const OutFunc & func);

    StringList & operator<<(const double & val);

    StringList & swapByIndices(const size_t & ndx1, const size_t & ndx2);

    StringList & swapByValues(const std::string & str1, const std::string & str2, const bool &caseSensitive=c_DEFAULT_CASE_SENSITIVE);

    std::size_t removeEmptyFields(bool removeWhitespace=c_DEFAULT_CASE_SENSITIVE);

    size_t indexOf(const std::string & str, bool caseSensitive=c_DEFAULT_CASE_SENSITIVE);

    size_t indexOfFirstThatStartsWith(const std::string & startStr, bool caseSensitive=c_DEFAULT_CASE_SENSITIVE);

    size_t indexOfFirstThatContainsWith(const std::string & containsStr, bool caseSensitive=c_DEFAULT_CASE_SENSITIVE);

    size_t indexOfFirstThatEndsWith(const std::string & endStr, bool caseSensitive=c_DEFAULT_CASE_SENSITIVE);

    size_t find(const std::string &str, const bool &caseSensitive=c_DEFAULT_CASE_SENSITIVE) const;

    template<class T> StringList & operator<<(const std::vector<T> & values)
    {
        for (size_t a1 = 0;a1 < values.size();++a1)
        {
            (*this)<<values[a1];
        }
    }

    template<class T> StringList & operator<<(const T & value)
    {
            std::ostringstream out;
            out << value;
            this->push_back(out.str());
            return *this;
    }


    int removeAllThatStartWith(const std::string & str);

    bool removeFirstThatEndsWith(const std::string &str);

    StringList & operator<<(const StringList & value);

    std::string operator[](size_t value)const;

    std::string get(const size_t & value)const;

    template<class T> void set(const size_t & index, const T & value)
    {
        if (index<this->size())
        {
            std::ostringstream out;
            out<<value;
            StringVector::operator[](index)=out.str();
        }
    }

    size_t remove(const std::string & value);

    void trimmed();

    std::string first()const;

    std::string last()const;

    std::string removeFirst();

    void inplaceTokenization(const std::string &token);

    void removeDuplicates();

    void chop();

    void replace(const std::string & oldStr, const std::string & newStr);

    std::string toVerboseString(const bool & newLine=false)const;

    std::list<std::string> toStdList() const;   

    size_t count(const std::string &value="") const;

    std::string toString(const std::string &seperator="") const;

    std::string toString(const std::string &preSeperator,const std::string & postSeperator) const;

    void toUpper(const size_t & startNdx=0);

    void toLower(const size_t & startNdx=0);

    void toUpperTrimmed(const size_t & startNdx=0);

    void toLowerTrimmed(const size_t & startNdx=0);

    bool contains(const std::string & value)const;

    void purge();

    size_t getNumBytes() const;

    size_t findFirstThatStartsWith(const std::string & str,const bool & caseSensitive=c_DEFAULT_CASE_SENSITIVE);

    size_t findFirstThatEndsWith(const std::string & str,const bool & caseSensitive=c_DEFAULT_CASE_SENSITIVE);
};

}}} //namespace
#endif // _CBTEK_COMMON_UTILITY_STRINGLIST_H_
