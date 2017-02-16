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

#include "utility/inc/StringBuilder.h"

namespace cbtek {
namespace common {
namespace utility {


StringBuilder::StringBuilder(size_t floatingPointPrecision)
{
    m_floatingPointPrecision=floatingPointPrecision;
}

StringBuilder::StringBuilder(const std::vector<std::string> &values,
                             size_t floatingPointPrecision)
{
    m_floatingPointPrecision=floatingPointPrecision;
    std::vector<std::string>::const_iterator itBeg = values.begin();
    std::vector<std::string>::const_iterator itEnd = values.end();
    while(itBeg!=itEnd)
    {
        (*this)<<(*itBeg);
        ++itBeg;
    }
}

StringBuilder::StringBuilder(const std::list<std::string> &values,
                             size_t floatingPointPrecision)
{
    m_floatingPointPrecision=floatingPointPrecision;
    std::list<std::string>::const_iterator itBeg = values.begin();
    std::list<std::string>::const_iterator itEnd = values.end();
    while(itBeg!=itEnd)
    {
        (*this)<<(*itBeg);
        ++itBeg;
    }
}

StringBuilder::StringBuilder(const std::set<std::string> &values,
                             size_t floatingPointPrecision)
{
    m_floatingPointPrecision=floatingPointPrecision;
    std::set<std::string>::const_iterator itBeg = values.begin();
    std::set<std::string>::const_iterator itEnd = values.end();
    while(itBeg!=itEnd)
    {
        (*this)<<(*itBeg);
        ++itBeg;
    }
}

StringBuilder::StringBuilder(const std::deque<std::string> &values,
                             size_t floatingPointPrecision)
{
    m_floatingPointPrecision=floatingPointPrecision;
    std::deque<std::string>::const_iterator itBeg = values.begin();
    std::deque<std::string>::const_iterator itEnd = values.end();
    while(itBeg!=itEnd)
    {
        (*this)<<(*itBeg);
        ++itBeg;
    }
}

StringBuilder::StringBuilder(const std::stack<std::string> &values,
                             size_t floatingPointPrecision)
{
    m_floatingPointPrecision=floatingPointPrecision;    
    std::stack<std::string> copy = values;
    while(copy.size() > 0)
    {
        (*this)<<(copy.top());
        copy.pop();
    }
}

StringBuilder::StringBuilder(const std::queue<std::string> &values,
                             size_t floatingPointPrecision)
{
    m_floatingPointPrecision = floatingPointPrecision;
    std::queue<std::string> copy = values;
    while(copy.size() > 0)
    {
        (*this)<<(copy.front());
        copy.pop();
    }
}

size_t StringBuilder::size() const
{
    return m_stringItems.size();
}

std::list<std::string> StringBuilder::toList() const
{
    return m_stringItems;
}

std::set<std::string> StringBuilder::toSet() const
{
    std::set<std::string> collection;
    toSet(collection);
    return collection;
}

std::vector<std::string> StringBuilder::toVector() const
{
    std::vector<std::string> collection;
    toVector(collection);
    return collection;
}

std::deque<std::string> StringBuilder::toDeque() const
{
    std::deque<std::string> collection;
    toDeque(collection);
    return collection;
}

std::stack<std::string> StringBuilder::toStack() const
{
    std::stack<std::string> collection;
    toStack(collection);
    return collection;
}

std::queue<std::string> StringBuilder::toQueue() const
{
    std::queue<std::string> collection;
    toQueue(collection);
    return collection;
}

void StringBuilder::toList(std::list<std::string> &listOut) const
{
    listOut = m_stringItems;
}

void StringBuilder::toVector(std::vector<std::string> &vecOut) const
{
    vecOut.resize(m_stringItems.size());
    std::list<std::string>::const_iterator itBeg = m_stringItems.begin();
    std::list<std::string>::const_iterator itEnd = m_stringItems.end();
    size_t index = 0;
    while(itBeg!=itEnd)
    {
        vecOut[index]=(*itBeg);
        ++itBeg;
        ++index;
    }
}

void StringBuilder::toSet(std::set<std::string> &setOut) const
{
    std::list<std::string>::const_iterator itBeg = m_stringItems.begin();
    std::list<std::string>::const_iterator itEnd = m_stringItems.end();
    while(itBeg!=itEnd)
    {
        setOut.insert(*itBeg);
        ++itBeg;
    }
}

void StringBuilder::toDeque(std::deque<std::string> &deqOut) const
{
    std::list<std::string>::const_iterator itBeg = m_stringItems.begin();
    std::list<std::string>::const_iterator itEnd = m_stringItems.end();
    while(itBeg!=itEnd)
    {
        deqOut.push_back(*itBeg);
        ++itBeg;
    }
}

void StringBuilder::toQueue(std::queue<std::string> &queOut) const
{
    std::list<std::string>::const_iterator itBeg = m_stringItems.begin();
    std::list<std::string>::const_iterator itEnd = m_stringItems.end();
    while(itBeg!=itEnd)
    {
        queOut.push(*itBeg);
        ++itBeg;
    }
}

void StringBuilder::toStack(std::stack<std::string> &stackOut) const
{
    std::list<std::string>::const_iterator itBeg = m_stringItems.begin();
    std::list<std::string>::const_iterator itEnd = m_stringItems.end();
    while(itBeg!=itEnd)
    {
        stackOut.push(*itBeg);
        ++itBeg;
    }
}

void StringBuilder::clear()
{
    m_stringItems.clear();
}

std::string StringBuilder::toString(const std::string &seperator) const
{
    std::ostringstream out;
    size_t count = m_stringItems.size();

    for (const std::string & str : m_stringItems)
    {
        out << str << ((count > 1) ? seperator : "") ;
        --count;
    }
    return out.str();
}

std::string StringBuilder::toString(const std::string & prefixString,
                                    const std::string & postFixString,
                                    const std::string &seperator) const
{
    std::ostringstream out;
    size_t count = m_stringItems.size();

    for (const std::string & str : m_stringItems)
    {
        out <<prefixString<< str <<postFixString << ((count > 1) ? seperator : "") ;
        --count;
    }
    return out.str();
}

StringBuilder &StringBuilder::operator <<(double value)
{
    std::ostringstream out;
    out.precision(m_floatingPointPrecision);
    out << std::fixed<<value;
    m_stringItems.push_back(out.str());
    return (*this);
}

StringBuilder::~StringBuilder()
{

}




}}}//end namespace


