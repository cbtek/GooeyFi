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

#ifndef _CBTEK_COMMON_UTILITY_STRINGBUILDER_H
#define _CBTEK_COMMON_UTILITY_STRINGBUILDER_H

#include "UtilityCommon.hpp"

#include <string>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <sstream>

namespace cbtek {
namespace common {
namespace utility {

class CBTEK_UTILS_DLL StringBuilder
{
    public:
    //! Constructor for StringBuilder
    /*!
        Detailed description for StringBuilder
    */
    StringBuilder(size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);


    /**
     * @brief StringBuilder
     * @param values
     * @param floatingPointPrecision
     */
    StringBuilder(const std::vector<std::string> & values,
                  size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);

    /**
     * @brief StringBuilder
     * @param values
     * @param floatingPointPrecision
     */
    StringBuilder(const std::list<std::string> & values,
                  size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);


    /**
     * @brief StringBuilder
     * @param values
     * @param floatingPointPrecision
     */
    StringBuilder(const std::set<std::string> & values,
                  size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);

    /**
     * @brief StringBuilder
     * @param values
     * @param floatingPointPrecision
     */
    StringBuilder(const std::deque<std::string> & values,
                  size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);

    /**
     * @brief StringBuilder
     * @param values
     * @param floatingPointPrecision
     */
    StringBuilder(const std::stack<std::string> & values,
                  size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);

    /**
     * @brief StringBuilder
     * @param values
     * @param floatingPointPrecision
     */
    StringBuilder(const std::queue<std::string> & values,
                  size_t floatingPointPrecision = c_DEFAULT_FLOATING_PRECISION);



    /**
     * @brief operator <<
     * @param value
     * @return
     */
    template <typename T>
    StringBuilder & operator <<(const T & value);

    /**
     * @brief operator <<
     * @param value
     * @return
     */
    StringBuilder & operator <<(double value);

    /**
     * @brief size
     * @return
     */
    size_t size() const;

    /**
     * @brief toList
     * @return
     */
    std::list<std::string> toList() const;

    /**
     * @brief toSet
     * @return
     */
    std::set<std::string> toSet() const;

    /**
     * @brief toVector
     * @return
     */
    std::vector<std::string> toVector() const;

    /**
     * @brief toDeque
     * @return
     */
    std::deque<std::string> toDeque() const;

    /**
     * @brief toStack
     * @return
     */
    std::stack<std::string> toStack() const;


    /**
     * @brief toQueue
     * @return
     */
    std::queue<std::string> toQueue() const;

    /**
     * @brief toList
     * @param listOut
     */
    void toList(std::list<std::string> & listOut) const;

    /**
     * @brief toVector
     * @param vecOut
     */
    void toVector(std::vector<std::string> &vecOut) const;

    /**
     * @brief toSet
     * @param setOut
     */
    void toSet(std::set<std::string> & setOut) const;

    /**
     * @brief toDeque
     * @param deqOut
     */
    void toDeque(std::deque<std::string> & deqOut) const;

    /**
     * @brief toQueue
     * @param queOut
     */
    void toQueue(std::queue<std::string> & queOut) const;

    /**
     * @brief toStack
     * @param stackOut
     */
    void toStack(std::stack<std::string> & stackOut) const;

    /**
     * @brief clear
     */
    void clear();


    /**
     * @brief toString
     * @param seperator
     * @return
     */
    std::string toString(const std::string & seperator="") const;

    /**
     * @brief toString
     * @param prefixString
     * @param postFixString
     * @param seperator
     * @return
     */
    std::string toString(const std::string & prefixString,
                         const std::string & postFixString,
                         const std::string &seperator="") const;
    //! Destructor
    ~StringBuilder();    

private:
    size_t m_floatingPointPrecision;   
    std::list<std::string> m_stringItems;
};

template <typename T>
StringBuilder & StringBuilder::operator << (const T & value)
{
    std::ostringstream out;
    out << value;
    m_stringItems.push_back(out.str());
    return (*this);
}
}}}//end namespace

#endif // _CBTEK_COMMON_UTILITY_STRINGBUILDER_H

