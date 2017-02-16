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


#ifndef _CBTEK_COMMON_UTILITY_STLUTILS_HPP_
#define _CBTEK_COMMON_UTILITY_STLUTILS_HPP_

#include "UtilityCommon.hpp"

#include <vector>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <iostream>
#include <ostream>

namespace cbtek {
namespace common {
namespace utility {
namespace STLUtils {

/**
* @brief Get vector of all map values
* @param sourceMap Source map
* @param[out] valuesOut Reference to vector of values
*/
template <typename K,typename V>
void getMapValues(const std::map<K,V> &sourceMap,
                  std::vector<V> &valuesOut)
{
    typename std::map<K,V>::const_iterator itBeg = sourceMap.begin();
    typename std::map<K,V>::const_iterator itEnd = sourceMap.end();

    while (itBeg!=itEnd)
    {
        valuesOut.push_back(itBeg->second);
        ++itBeg;
    }
}

/**
* @brief Get vector of all map keys
* @param sourceMap Source map
* @param[out] keysOut Reference to vector of keys
*/
template <typename K,typename V>
void getMapKeys(const std::map<K,V> &sourceMap,
                std::vector<K> &keysOut)
{
    typename std::map<K,V>::const_iterator itBeg = sourceMap.begin();
    typename std::map<K,V>::const_iterator itEnd = sourceMap.end();

    while (itBeg!=itEnd)
    {
        keysOut.push_back(itBeg->first);
        ++itBeg;
    }
}

/**
* @brief Get vector of all map keys and values
* @param sourceMap Source map
* @param keysOut Reference to vector of keys
* @param[out] valuesOut Reference to vector of values
*/
template <typename K,typename V>
void getMapKeysAndValues(const std::map<K,V> &sourceMap,
                         std::vector<K> &keysOut,
                         std::vector<V> &valuesOut)
{
    typename std::map<K,V>::const_iterator itBeg = sourceMap.begin();
    typename std::map<K,V>::const_iterator itEnd = sourceMap.end();

    while (itBeg!=itEnd)
    {
        keysOut.push_back(itBeg->first);
        valuesOut.push_back(itBeg->second);
        ++itBeg;
    }
}

/**
* @brief This function converts all values in a set to a vector of the
* same type.
* @param valueSet The set of values to convert into a vector
* @param[out] vectorOut Reference to the vector to be populated
*/
template <typename T>
void toVector(const std::set<T> & valueSet,
              std::vector<T> & vectorOut)
{
    typename std::set<T>::iterator itBeg = valueSet.begin();
    typename std::set<T>::iterator itEnd = valueSet.end();

    while(itBeg!=itEnd)
    {
        vectorOut.push_back(*itBeg);
        ++itBeg;
    }
}


/**
* @brief This function converts all values in a
*        list to a vector of the same type
* @param valueList The list of values to convert into a vector
* @param[out] vectorOut Reference to the vector to be populated
*/
template <typename T>
void toVector(const std::list<T> & valueList,
              std::vector<T> & vectorOut)
{

    typename std::list<T>::iterator itBeg = valueList.begin();
    typename std::list<T>::iterator itEnd = valueList.end();

    while (itBeg != itEnd)
    {
        vectorOut.push_back(*itBeg);
        ++itBeg;
    }
}

/**
* @brief Writes vector of type (T) to output stream
* @param[out] out Reference to output stream
* @param itemVector Vector to write to stream
*/
template <typename T>
void toStream(std::ostream & out,
              const std::vector<T> & itemVector)
{
    typename std::vector<T>::const_iterator itBeg = itemVector.begin();
    typename std::vector<T>::const_iterator itEnd = itemVector.end();

    size_t count = 0;    
    out <<std::string("vector : ")<<itemVector.size()<<std::endl;
    while (itBeg != itEnd)
    {
        out << std::string("    [")<<count<<std::string("]: ")<<(*itBeg)<<std::endl;
        ++itBeg;
        ++count;
    }
}

/**
* @brief Writes set of type (T) to output stream
* @param[out] out Reference to output stream
* @param itemSet Set to write to stream
*/
template <typename T>
void toStream(std::ostream & out,
              const std::set<T> & itemSet)
{
    typename std::set<T>::const_iterator itBeg = itemSet.begin();
    typename std::set<T>::const_iterator itEnd = itemSet.end();

    out <<std::string("set : ")<<itemSet.size()<<std::endl;
    size_t count = 0;
    while (itBeg != itEnd)
    {
        out << std::string("    [")<<count<<std::string("]: ")<<(*itBeg)<< std::endl;
        ++itBeg;
        ++count;
    }
}

/**
* @brief Writes map of type (K,V) to output stream
* @param[out] out Reference to output stream
* @param itemMap Map to write to stream
*/
template <typename K, typename V>
void toStream(std::ostream & out,
              const std::map<K,V> & itemMap)
{
    typename std::map<K,V>::const_iterator itBeg = itemMap.begin();
    typename std::map<K,V>::const_iterator itEnd = itemMap.end();

    out <<std::string("map : ")<<itemMap.size()<<std::endl;
    while (itBeg != itEnd)
    {
        out <<std::string("    [")<<itBeg->first<<std::string("]: ")<<(itBeg->second)<<std::endl;
        ++itBeg;
    }
}

/**
* @brief Writes list of type (T) to output stream
* @param[out] out Reference to output stream
* @param itemList List to write to stream
*/
template <typename T>
void toStream(std::ostream & out,
              const std::list<T> & itemList)
{
    typename std::list<T>::const_iterator itBeg = itemList.begin();
    typename std::list<T>::const_iterator itEnd = itemList.end();

    out <<std::string("list : ")<<itemList.size()<<std::endl;
    size_t count = 0;
    while (itBeg != itEnd)
    {
        out << std::string("    [")<<count<<std::string("]: ")<<(*itBeg)<<std::endl;
        ++itBeg;
        ++count;
    }
}

}}}}//end namespace

#endif

