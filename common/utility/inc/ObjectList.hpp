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
#ifndef _CBTEK_COMMON_UTILITY_OBJECTLIST_HPP_
#define _CBTEK_COMMON_UTILITY_OBJECTLIST_HPP_

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

#include "utility/inc/UtilityCommon.hpp"
#include "utility/inc/Random.h"

namespace cbtek{
namespace common{
namespace utility{

template <typename T>
class CBTEK_UTILS_DLL ObjectList  : public std::vector<T>
{
    public:    
        ObjectList();

        ObjectList & operator<<(const T & value);

        ObjectList & operator<<(const ObjectList<T> & value);

        bool contains(const T & value) const;

        bool contains(const T & value);

        size_t getLastIndex() const;

        void removeAt(size_t index);

        bool removeFirst();

        bool removeLast();

        void pushFront(const T & value);

        T takeAt(size_t index);

        size_t add(const T & value);

        size_t indexOf(const T & value);

        bool insertAfterValue(const T & insertAfterThisValue, const T & valueToBeInserted);

        bool insertBeforeValue(const T & insertBeforeThisValue, const T & valueToBeInserted);

        bool insertAfterIndex(size_t index, const T & valueToBeInserted);

        bool insertBeforeIndex(size_t index, const T & valueToBeInserted);

        const T & getRandomValue() const;

        void sort();

        void reverseSort();

        T getNext();

    private:
        static Random ms_RANDOM;
        size_t m_next;
        static size_t npos;
};


template <typename T>
ObjectList<T> & ObjectList<T>::operator<<(const ObjectList<T> & values)
{
    for (size_t a1 = 0;a1,values.size();++a1)
    {
        this->add(values[a1]);
    }
}

template <typename T>
Random ObjectList<T>::ms_RANDOM = Random();

template <typename T>
ObjectList<T>::ObjectList()
{
    m_next=0;
}

template <typename T>
const T & ObjectList<T>::getRandomValue() const
{
    size_t index = ms_RANDOM.next(this->size()-1);
    return this->operator [](index);
}

template <typename T>
void ObjectList<T>::sort()
{
    std::sort(this->begin(),this->end());
}

template <typename T>
void ObjectList<T>::removeAt(size_t index)
{
    if (index<this->size())
    {
        this->erase(this->begin()+index);
    }
}

template <typename T>
T ObjectList<T>::takeAt(size_t index)
{
    T t;
    if (index<this->size())
    {
        t= this->operator [](index);
        this->erase(this->begin()+index);
    }
    return t;
}

template <typename T>
void ObjectList<T>::reverseSort()
{
    this->sort();
    std::reverse(this->begin(),this->end());
}

template <typename T>
T ObjectList<T>::getNext()
{
    T value;
    if (m_next>=this->size())
    {
        m_next=0;
    }
    value = this->operator [](m_next);
    m_next++;
    return value;
}

template <typename T>
size_t ObjectList<T>::npos = std::numeric_limits<size_t>::max();

template <typename T>
ObjectList<T> &ObjectList<T>::operator <<(const T &value)
{
    this->push_back(value);
    return (*this);
}

template <typename T>
size_t ObjectList<T>::indexOf(const T & value)
{
    for(size_t a1= 0;a1<this->size();++a1)
    {
        if ((*this).at(a1)==value)
        {
            return a1;
        }
    }
    return npos;
}


template <typename T>
bool ObjectList<T>::contains(const T &value)
{
    for (size_t a1 = 0;a1<this->size();++a1)
    {
        if ((*this).at(a1)==value)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
bool ObjectList<T>::contains(const T &value) const
{
    for (size_t a1 = 0;a1<this->size();++a1)
    {
        if ((*this).at(a1)==value)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
size_t ObjectList<T>::getLastIndex() const
{
    return this->size() > 0 ? this->size()-1 : ObjectList::npos;
}

template<typename T>
bool ObjectList<T>::removeLast()
{
    if (this->size()>0)
    {
        this->erase(this->begin()+(this->size()-1));
        return true;
    }
    return false;
}

template<typename T>
bool ObjectList<T>::removeFirst()
{
    if (this->size()>0)
    {
        this->erase(this->begin()+0);
        return true;
    }
    return false;
}

template<typename T>
void ObjectList<T>::pushFront(const T & value)
{
    std::vector<T>::insert(this->begin()+0,value);
}

template<typename T>
size_t ObjectList<T>::add(const T & value)
{
    this->push_back(value);
    return this->size()-1;
}

template<typename T>
void add(const ObjectList<T> & items)
{
    for (size_t a1 = 0;a1<items.size();++a1)
    {
        push_back(items[a1]);
    }
}


template<typename T>
bool ObjectList<T>::insertAfterValue(const T & insertAfterThisValue, const T & valueToBeInserted)
{
    size_t index = indexOf(insertAfterThisValue);
    if (index>=this->size())return false;
    return insertAfterIndex(index,valueToBeInserted);
}

template<typename T>
bool ObjectList<T>::insertBeforeValue(const T & insertBeforeThisValue, const T & valueToBeInserted)
{
    size_t index = indexOf(insertBeforeThisValue);
    if (index>=this->size())return false;
    return insertBeforeIndex(index,valueToBeInserted);
}

template<typename T>
bool ObjectList<T>::insertAfterIndex(size_t index, const T & valueToBeInserted)
{
    if ((index+1)== this->size())
    {
        this->push_back(valueToBeInserted);
        return true;
    }
    if ((index+1)<this->size())
    {
        this->insert(this->begin()+(index+1),valueToBeInserted);
        return true;
    }
    return false;
}

template<typename T>
bool ObjectList<T>::insertBeforeIndex(size_t index, const T & valueToBeInserted)
{
    if (index!=0 && (index-1)<this->size())
    {
        this->insert(this->begin()+(index-1),valueToBeInserted);
        return true;
    }
    return false;

}

//typedefs
typedef ObjectList<std::uint8_t> UInt8List;
typedef ObjectList<std::uint16_t> UInt16List;
typedef ObjectList<std::uint32_t> UInt32List;
typedef ObjectList<std::uint64_t> UInt64List;
typedef ObjectList<std::int8_t> Int8List;
typedef ObjectList<std::int16_t> Int16List;
typedef ObjectList<std::int32_t> Int32List;
typedef ObjectList<std::int64_t> Int64List;
typedef ObjectList<size_t> SizeTList;
typedef UInt8List::iterator UInt8ListIter;
typedef UInt16List::iterator UInt16ListIter;
typedef UInt32List::iterator UInt32ListIter;
typedef UInt64List::iterator UInt64ListIter;
typedef UInt8List::const_iterator UInt8ListConstIter;
typedef UInt16List::const_iterator UInt16ListConstIter;
typedef UInt32List::const_iterator UInt32ListConstIter;
typedef UInt64List::const_iterator UInt64ListConstIter;
typedef Int8List::iterator Int8ListIter;
typedef Int16List::iterator Int16ListIter;
typedef Int32List::iterator Int32ListIter;
typedef Int64List::iterator Int64ListIter;
typedef SizeTList::iterator SizeTListIter;
typedef Int8List::const_iterator Int8ListConstIter;
typedef Int16List::const_iterator Int16ListConstIter;
typedef Int32List::const_iterator Int32ListConstIter;
typedef Int64List::const_iterator Int64ListConstIter;
typedef SizeTList::const_iterator SizeTListConstIter;

}}}//namespace
#endif // _CBTEK_COMMON_UTILITY_OBJECTLIST_HPP_
