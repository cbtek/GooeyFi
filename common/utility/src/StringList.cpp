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

#include "StringList.h"
#include "StringUtils.hpp"

namespace cbtek {
namespace common {
namespace utility {

size_t StringList::npos=-1;
using namespace std;


StringList &StringList::operator <<(const StringList &stringList)
{
    for (size_t a1 = 0;a1<stringList.size();a1++)
    {
        std::string value = stringList[a1];
        this->push_back(value);
    }
    return *this;
}

std::string StringList::operator [](size_t value) const
{
    return this->get(value);
}

std::string StringList::get(const size_t &value) const
{
    return (value<this->size()) ? std::vector<std::string>::operator[](value):"";
}


    StringList &StringList::swapByIndices(const size_t &ndx1, const size_t &ndx2)
    {

        if (ndx1<size() && ndx2<size() )
        {
            std::string str1=this->operator [](ndx1);
            set(ndx1,(*this)[ndx2]);
            set(ndx2,str1);
        }
        return (*this);
    }

    StringList &StringList::swapByValues(const string &str1, const string &str2, const bool & caseSensitive)
    {
        return swapByIndices(find(str1,caseSensitive),find(str2,caseSensitive));
    }

    size_t StringList::removeEmptyFields(bool removeWhitespace)
    {
        size_t count = 0;
        for (int a1 = this->size()-1;a1>=0;--a1)
        {
            if (removeWhitespace)
            {
                if (StringUtils::trimmed(this->operator [](a1)).size() == 0)
                {
                    this->erase(this->begin()+a1);
                    ++count;
                }
            }
            else
            {
                if ((this->operator [](a1)).size() == 0)
                {
                    this->erase(this->begin()+a1);
                    ++count;
                }
            }
        }
        return count;
    }

    size_t StringList::indexOf(const string &str, bool caseSensitive)
    {
        for(size_t a1 = 0;a1<this->size();++a1)
        {
            if (caseSensitive && str==this->operator [](a1))
            {
                return a1;
            }
            else if (!caseSensitive && StringUtils::toLower(str)==StringUtils::toLower(this->operator [](a1)))
            {
                return a1;
            }
        }
        return std::string::npos;
    }

    size_t StringList::indexOfFirstThatStartsWith(const string &startStr, bool caseSensitive)
    {
        for(size_t a1 = 0;a1<this->size();++a1)
        {
            if (StringUtils::startsWith(this->operator [](a1),startStr,caseSensitive))
            {
                return a1;
            }
        }
        return std::string::npos;
    }

    size_t StringList::indexOfFirstThatContainsWith(const string &containsStr, bool caseSensitive)
    {
        for(size_t a1 = 0;a1<this->size();++a1)
        {
            if (StringUtils::contains(this->operator [](a1),containsStr,caseSensitive))
            {
                return a1;
            }
        }
        return std::string::npos;
    }

    size_t StringList::indexOfFirstThatEndsWith(const string &endStr, bool caseSensitive)
    {
        for(size_t a1 = 0;a1<this->size();++a1)
        {
            if (StringUtils::endsWith(this->operator [](a1),endStr,caseSensitive))
            {
                return a1;
            }
        }
        return std::string::npos;
    }


    size_t StringList::find(const string &str, const bool &caseSensitive) const
    {

        //Will replace following code with this later
        //    StringList::iterator it = std::find(begin(),end(),str);
        //    if (it!=end())
        //    {
        //        return std::distance(begin(),it);
        //    }
        if (caseSensitive)
        {
            for (size_t a1 = 0;a1<size();++a1)
            {
                if (str==operator [](a1))
                {
                    return a1;
                }
            }
        }
        else
        {
            for (size_t a1 = 0;a1<size();++a1)
            {
                if (StringUtils::toUpper(str)==StringUtils::toUpper(this->operator [](a1)))
                {
                    return a1;
                }
            }
        }
        return StringList::npos;
    }

bool StringList::removeFirstThatEndsWith(const string &str)
{
    for (int a1 = this->size()-1;a1>=0;--a1)
    {
       if (StringUtils::endsWith(this->operator [](a1),str))
       {
           this->erase(this->begin()+a1);
           return true;
       }
    }
    return false;
}
int StringList::removeAllThatStartWith(const string &str)
{
    int count=0;
    for (int a1 = this->size()-1;a1>=0;--a1)
    {
       if (StringUtils::startsWith(this->operator [](a1),str))
       {
           this->erase(this->begin()+a1);
           count++;
       }
    }
    return count;
}

string StringList::toVerboseString(const bool &useNL) const
{
    std::ostringstream out;
    const_iterator it=this->begin();
    int count = 0;
    while(it!=this->end())
    {
        out <<count<<":["<< *it<<"] "<<(useNL?"\n":"");
        ++it;
        ++count;
    }
    return out.str();
}

string StringList::toString(const std::string &seperator) const
{

    const_iterator it=this->begin();
    if (this->size()==1)
    {
        return *it;
    }


    std::ostringstream out;
    if (it==this->end())
    {
        return "";
    }
    out <<(*it);
    ++it;
    while(it!=this->end())
    {
        out <<seperator<<*it;
        ++it;
    }
    return out.str();
}

string StringList::toString(const std::string &preSeperator,const std::string & postSeperator) const
{

    const_iterator it=this->begin();
    if (this->size()==1)
    {
        return preSeperator+(*it)+postSeperator;
    }


    std::ostringstream out;
    if (it==this->end())
    {
        return "";
    }

    while(it!=this->end())
    {
        out <<preSeperator<<*it<<postSeperator;
        ++it;
    }
    return out.str();
}

void StringList::toUpper(const size_t &startNdx)
{
    for (size_t i=startNdx;i<this->size();++i)
    {
        if (this->operator [](i)==StringUtils::toUpper(this->operator [](i))){}
    }
}

void StringList::toLower(const size_t &startNdx)
{
    for (size_t i=startNdx;i<this->size();++i)
    {
        if (this->operator [](i)==StringUtils::toLower(this->operator [](i))){}
    }
}

void StringList::toUpperTrimmed(const size_t &startNdx)
{
    for (size_t i=startNdx;i<this->size();++i)
    {
        if (this->operator [](i)==StringUtils::toUpperTrimmed(this->operator [](i))){}
    }
}

void StringList::toLowerTrimmed(const size_t &startNdx)
{
    for (size_t i=startNdx;i<this->size();++i)
    {
        if (this->operator [](i)==StringUtils::toLowerTrimmed(this->operator [](i))){}
    }
}


bool StringList::contains(const string &value) const
{
    for (size_t i=0;i<this->size();++i)
    {
        if (this->operator [](i)==value)
        {
            return true;
        }
    }
    return false;
}

void StringList::purge()
{
    this->remove("");
}

size_t StringList::getNumBytes() const
{
    size_t byteCount=0;
    for (size_t a1 = 0;a1<size();++a1)
    {
        std::string str=this->operator [](a1);
        byteCount+=str.size();
    }
    return byteCount;
}

size_t StringList::findFirstThatStartsWith(const string &str, const bool &caseSensitive)
{
    if (caseSensitive)
       {
           for (size_t a1 = 0;a1<size();++a1)
           {
               if (StringUtils::startsWith(operator [](a1),str))
               {
                   return a1;
               }
           }
       }
       else
       {
           for (size_t a1 = 0;a1<size();++a1)
           {
               if (StringUtils::startsWith(StringUtils::toUpper(this->operator [](a1)),StringUtils::toUpper(str)))
               {
                   return a1;
               }
           }
       }
    return StringList::npos;
}

size_t StringList::findFirstThatEndsWith(const string &str, const bool &caseSensitive)
{
    if (caseSensitive)
       {
           for (size_t a1 = 0;a1<size();++a1)
           {
               if (StringUtils::endsWith(operator [](a1),str))
               {
                   return a1;
               }
           }
       }
       else
       {
           for (size_t a1 = 0;a1<size();++a1)
           {
               if (StringUtils::endsWith(StringUtils::toUpper(this->operator [](a1)),StringUtils::toUpper(str)))
               {
                   return a1;
               }
           }
       }
    return StringList::npos;
}

size_t StringList::remove(const std::string &value)
{
    size_t count=0;
  for (int x = this->size()-1;x>=0;--x)
  {
      if (this->operator [](x)==value)
      {
          this->erase(this->begin()+x);
          count++;
      }
  }
  return count;
}

void StringList::trimmed()
{
    iterator it=this->begin();
    while(it!=this->end())
    {
        *it= StringUtils::trimmed(*it);
        ++it;
    }
}

string StringList::first() const
{
    if (this->size()>0)
    {
        StringListConstIter it = this->begin();
        return *it;
    }
    return "";
}

string StringList::last() const
{
    if (this->size()>0)
    {
        StringListConstIter it = this->end();
        it--;
        return *it;
    }
    return "";
}

string StringList::removeFirst()
{
    if (this->size())
    {
        std::string value = this->front();
        this->erase(this->begin()+0);
        return value;
    }
    return "";
}

void StringList::inplaceTokenization(const std::string &token)
{
    StringList values;
    for (size_t a1 =0;a1<this->size();++a1)
    {
        std::vector<std::string> splitValues = StringUtils::split(this->operator [](a1),token);
        values << splitValues;
    }
    (*this)=values;
}

void StringList::removeDuplicates()
{
    std::map<std::string,std::string> uniques;
    std::map<size_t,std::string> itemsSorted;
    size_t counter=0;
    for (size_t a1 = 0;a1<this->size();++a1)
    {
        std::string value=(*this)[a1];
        if (!uniques.count(value))
        {
             itemsSorted[counter]=value;
             uniques[value]=value;
             counter++;
        }
    }

    this->clear();
    for (std::map<size_t,std::string>::iterator it = itemsSorted.begin();it!=itemsSorted.end();++it)
    {
        this->push_back(it->second);
    }
}

size_t StringList::count(const std::string &value) const
{
    if (value.size()==0)
    {
        return this->size();
    }
    const_iterator it=this->begin();
    size_t count = 0;
    while(it!=this->end())
    {
        if(*it==value)
        {
            ++count;
        }
        ++it;
    }
    return count;
}

void StringList::chop()
{
    if (this->size()>0)
    {
        this->pop_back();
    }
}

void StringList::replace(const std::string &oldStr, const std::string &newStr)
{
    for (size_t a1 = 0;a1<this->size();++a1)
    {
        (*this)[a1]=StringUtils::replace(this->operator [](a1),oldStr,newStr);
    }
}

std::list<string> StringList::toStdList() const
{
    std::list<std::string> values;
    for(size_t a1 = 0;a1<this->size();++a1)
    {
        values.push_back((*this)[a1]);
    }
    return values;
}


StringList::StringList()
{
}

StringList::StringList(const std::string & value)
{
    this->push_back(value);
}

StringList::StringList(const std::vector<std::string> &  values)
{
    for(size_t a1 = 0;a1<values.size();++a1)
    {
        this->push_back(values[a1]);
    }
}

StringList::StringList(const std::list<std::string> & strList)
{
    std::list<std::string>::const_iterator it=strList.begin();
    while(it!=strList.end())
    {
        this->push_back(*it);
        ++it;
    }

}

StringList &StringList::operator <<(const OutFunc &func)
{
    std::ostringstream out;
    func(out);
    this->push_back(out.str());
    return *this;

}

StringList &StringList::operator <<(const double &val)
{
    this->push_back(StringUtils::toString(val,c_DEFAULT_FLOATING_PRECISION));
    return *this;
}

}}}//namespace

