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



#ifndef _CBTEK_COMMON_UTILITY_XMLDATAELEMENT_H
#define _CBTEK_COMMON_UTILITY_XMLDATAELEMENT_H

#include <map>
#include <vector>
#include <sstream>
#include <string>

#include "StringUtils.hpp"
#include "UtilityCommon.hpp"

namespace cbtek {
namespace common {
namespace utility {

class XMLDataElement;
typedef std::vector<XMLDataElement*> ChildElementVector;
typedef std::vector<std::pair<std::string,std::string> > AttributeVector;

class CBTEK_UTILS_DLL XMLDataElement
{
public:
    XMLDataElement();
    XMLDataElement(const XMLDataElement & element);
    ~XMLDataElement();

    const AttributeVector &getAttributes() const;
    const ChildElementVector & getChildren() const;

    const std::string & getElementName() const;
    const std::string & getElementData() const;

    std::string getAttributeValue(const std::string & attributeName,bool caseSensitive=false) const;
    std::string getAttributeName(size_t index)const;
    std::string getAttributeValue(size_t index) const;    

    XMLDataElement * getParent() const;
    XMLDataElement * getNextSibling() const;
    XMLDataElement * getChildAt(size_t index)const;
    XMLDataElement * getChild(const std::string & name) const;

    bool attributeExists(const std::string &attributeName,bool caseSensitive=false) const;

    bool hasChildren() const;
    bool childExists(size_t index);
    bool childExists(const std::string & name, bool caseSensitive=false);
    size_t getNumChildren() const;
    size_t getNumAttributes() const;
    size_t getLocalIndex() const;

    size_t getChildIndex(const XMLDataElement * child) const;

    void setElementData(const std::string & data);
    void setElementName(const std::string & name);
    void addAttribute(const std::string & attributeName, const std::string & attributeValue);
    void addChild(XMLDataElement * child);
    void setParent(XMLDataElement * parent);
    void setLocalIndex(size_t index);
    XMLDataElement * find(const std::string & name, const bool & caseSensitive=false);

    const XMLDataElement * find(const std::string & name, const bool & caseSensitive=false) const;
    void addAttribute(const std::string & attributeName, const float & attributeValue);
    void addAttribute(const std::string & attributeName, const double & attributeValue);

    template<typename T>
    void addAttribute(const std::string & attributeName, const T & attributeValue)
    {
        m_Attributes.push_back(
                    std::make_pair(attributeName,
                                              StringUtils::toString(attributeValue)));
    }

    template <typename Number>
    Number getAttributeValueAsType(const std::string& attributeName) const
    {
        Number valueNumber;
        std::string valueStr = getAttributeValue(attributeName);
        std::stringstream in(valueStr);
        in>>valueNumber;
        return valueNumber;
    }

protected:

    XMLDataElement *findInSubTree(const std::string & name,
                                  const XMLDataElement *element,
                                  const bool &caseSensitive);

    const XMLDataElement *findInSubTree(const std::string & name,
                                        const XMLDataElement *element,
                                        const bool &caseSensitive) const;
    size_t m_LocalIndex;

    #ifdef _MSC_VER
    #   pragma warning( push )
    #   pragma warning( disable : 4251 )
    #endif        
        std::string m_Name;
        std::string m_Data;
        std::string m_Temp;
        AttributeVector m_Attributes;
        ChildElementVector m_ChildElementVector;
        XMLDataElement * m_Parent;
    #ifdef _MSC_VER
    #   pragma warning( pop )
    #endif          
};
}}}//namespace
#endif // XMLDATAELEMENT_H

