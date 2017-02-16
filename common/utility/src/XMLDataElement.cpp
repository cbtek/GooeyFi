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
#include "utility/inc/XMLDataElement.h"
#include "utility/inc/StringUtils.hpp"

namespace cbtek {
namespace common {
namespace utility {

XMLDataElement::XMLDataElement()
{
    m_Parent=0;
    m_LocalIndex=0;
}

XMLDataElement::XMLDataElement(const XMLDataElement &element)
{
    m_Attributes = element.getAttributes();
    m_Name=element.getElementName();
    m_Data=element.getElementData();
    m_LocalIndex=element.getLocalIndex();
    m_Parent=0;
    for (size_t a1 = 0;a1<element.getNumChildren();++a1)
    {
        m_ChildElementVector.push_back(new XMLDataElement(*element.getChildAt(a1)));
    }
}

XMLDataElement::~XMLDataElement()
{
    for (size_t a1 = 0;a1<m_ChildElementVector.size();a1++)
    {
        XMLDataElement * child= m_ChildElementVector[a1];
        if (child)
        {
            delete child;
            child=0;
        }
    }

    m_ChildElementVector.clear();
}

const std::string &XMLDataElement::getElementName() const
{
    return m_Name;
}

const AttributeVector &XMLDataElement::getAttributes() const
{
    return m_Attributes;
}

size_t XMLDataElement::getNumAttributes() const
{
    return m_Attributes.size();
}

std::string XMLDataElement::getAttributeName(size_t index) const
{
    if (index<m_Attributes.size())
    {
        return m_Attributes[index].first;
    }
    return "";
}

std::string XMLDataElement::getAttributeValue(size_t index) const
{
    if (index<m_Attributes.size())
    {
        return m_Attributes[index].second;
    }
    return "";
}

bool XMLDataElement::attributeExists(const std::string & attributeName, bool caseSensitive) const
{
    for(size_t a1 = 0;a1<m_Attributes.size();a1++)
    {
        if (caseSensitive)
        {
            if (m_Attributes[a1].first==attributeName)
            {
                return true;
            }
        }
        else
        {
            if (StringUtils::toUpper(m_Attributes[a1].first)==StringUtils::toUpper(attributeName))
            {
                return true;
            }
        }
    }
    return false;
}


const std::string &XMLDataElement::getElementData() const
{
    return m_Data;
}

std::string XMLDataElement::getAttributeValue(const std::string & attributeName,
                                              bool caseSensitive) const
{

    for(size_t a1 = 0;a1<m_Attributes.size();a1++)
    {
        if (caseSensitive)
        {
            if (m_Attributes[a1].first==attributeName)
            {
                return m_Attributes[a1].second;
            }
        }
        else
        {
            if (StringUtils::toUpper(m_Attributes[a1].first)==StringUtils::toUpper(attributeName))
            {
                return m_Attributes[a1].second;
            }
        }
    }
    return "";
}

const ChildElementVector &XMLDataElement::getChildren() const
{
    return m_ChildElementVector;
}

bool XMLDataElement::hasChildren() const
{
    return m_ChildElementVector.size()>0;
}

XMLDataElement *XMLDataElement::getChildAt(size_t index) const
{
    return (index < m_ChildElementVector.size())?m_ChildElementVector[index]:NULL;
}

XMLDataElement *XMLDataElement::getChild(const std::string &name) const
{
    for(XMLDataElement * element: m_ChildElementVector)
    {
        if (StringUtils::equals(element->getElementName(),name))
        {
            return element;
        }
    }
    return NULL;
}

bool XMLDataElement::childExists(const std::string &name, bool caseSensitive)
{
    for (size_t a1 = 0;a1<m_ChildElementVector.size();a1++)
    {
        XMLDataElement * child= m_ChildElementVector[a1];
        if (caseSensitive)
        {
            if (child->getElementName()==name)
            {
                return true;
            }
        }
        else
        {
            if (StringUtils::toUpper(child->getElementName())==StringUtils::toUpper(name))
            {
                return true;
            }
        }
    }
    return false;

}

size_t XMLDataElement::getNumChildren() const
{
    return m_ChildElementVector.size();
}

void XMLDataElement::setElementData(const std::string &data)
{
    m_Data=data;
}

void XMLDataElement::setElementName(const std::string &name)
{
    m_Name=name;
}

void XMLDataElement::addAttribute(const std::string &attributeName,
                                  const std::string &attributeValue)
{
    m_Attributes.push_back(std::make_pair(attributeName,attributeValue));
}

void XMLDataElement::addChild(XMLDataElement *child)
{
    m_ChildElementVector.push_back(child);
}

void XMLDataElement::setParent(XMLDataElement *parent)
{
    m_Parent=parent;
}

XMLDataElement *XMLDataElement::getParent() const
{
    return m_Parent;
}

size_t XMLDataElement::getLocalIndex() const
{
    return m_LocalIndex;
}

size_t XMLDataElement::getChildIndex(const XMLDataElement *child) const
{
    for (size_t a1 = 0;a1<m_ChildElementVector.size();++a1)
    {
        if (child==m_ChildElementVector[a1])
        {
            return a1;
        }
    }
    return 0;
}

void XMLDataElement::setLocalIndex(size_t index)
{
    m_LocalIndex=index;
}

const XMLDataElement *XMLDataElement::find(const std::string &name,
                                           const bool &caseSensitive) const
{
    return findInSubTree(name,this,caseSensitive);
}

XMLDataElement *XMLDataElement::find(const std::string &name,
                                     const bool &caseSensitive)
{
    return findInSubTree(name,this,caseSensitive);
}

void XMLDataElement::addAttribute(const std::string &attributeName,
                                  const float &attributeValue)
{
    m_Attributes.push_back(std::make_pair(attributeName,StringUtils::toString(attributeValue)));
}

void XMLDataElement::addAttribute(const std::string &attributeName,
                                  const double &attributeValue)
{
    m_Attributes.push_back(std::make_pair(attributeName,StringUtils::toString(attributeValue)));
}

XMLDataElement *XMLDataElement::findInSubTree(const std::string & name,
                                              const XMLDataElement * element,
                                              const bool &caseSensitive)
{
    for (size_t a1 = 0;a1<element->getNumChildren();++a1)
    {
        XMLDataElement * child = element->getChildAt(a1);
        if (caseSensitive)
        {
            if (name==child->getElementName())
            {
                return child;
            }
        }
        else
        {
            if (StringUtils::toUpper(name)==StringUtils::toUpper(child->getElementName()))
            {
                return child;
            }
        }

        if (child->getNumChildren()>0)
        {
            XMLDataElement * subChild = findInSubTree(name,child,caseSensitive);
            if (subChild)
            {
                return subChild;
            }
        }
    }
    return NULL;
}


const XMLDataElement *XMLDataElement::findInSubTree(const std::string & name,
                                                    const XMLDataElement * element,
                                                    const bool &caseSensitive) const
{
    for (size_t a1 = 0;a1<element->getNumChildren();++a1)
    {
        const XMLDataElement * child = element->getChildAt(a1);
        if (caseSensitive)
        {
            if (name==child->getElementName())
            {
                return child;
            }
        }
        else
        {
            if (StringUtils::toUpper(name)==StringUtils::toUpper(child->getElementName()))
            {
                return child;
            }
        }

        if (child->getNumChildren()>0)
        {
            const XMLDataElement * subChild = findInSubTree(name,child,caseSensitive);
            if (subChild)
            {
                return subChild;
            }
        }
    }
    return NULL;
}

XMLDataElement *XMLDataElement::getNextSibling() const
{
    if (m_Parent)
    {
        size_t ndx = m_Parent->getChildIndex(this);
        return m_Parent->getChildAt(ndx+1);
    }
    return NULL;
}

}}}//namespace
