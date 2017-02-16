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

#include "utility/inc/XMLReader.h"
#include "utility/inc/Exception.hpp"
#include "utility/inc/FileUtils.hpp"

namespace cbtek {
namespace common {
namespace utility {

XMLReader::XMLReader()
{
    this->m_Index=0;
    this->m_LineCount=0;
    this->m_Depth=0;
    this->m_ColumnCount=0;
    this->m_LineCount=0;
    this->m_Current=NULL;    
    this->m_Root.setElementName("ROOT");
    this->m_Root.setParent(0);
    this->m_Initialized=false;
}


XMLReader::~XMLReader()
{    
}

XMLDataElement *XMLReader::getRoot()
{
    return &this->m_Root;
}

const XMLDataElement *XMLReader::getRoot() const
{
    return &this->m_Root;
}


void XMLReader::reset()
{
    this->m_Current=&this->m_Root;
}

bool XMLReader::isValid() const
{
    return this->m_Initialized;
}

size_t XMLReader::getDepth() const
{
    return this->m_Depth;
}

void XMLReader::clear()
{
    this->m_ParseString.clear();
    this->m_PeekToken=0;
    this->m_Index=0;
    this->m_LineCount=0;
    this->m_Depth=0;
    this->m_ColumnCount=0;
    this->m_LineCount=0;
    this->m_Current=NULL;    
    this->m_Root.setElementName("ROOT");
    this->m_Root.setParent(NULL);
    this->m_Initialized=false;
}

XMLDataElement *XMLReader::getFirstElement()
{
    if (this->m_Root.getNumChildren()>0)
    {
        return this->m_Root.getChildAt(0);
    }
    else return &this->m_Root;
}

XMLDataElement *XMLReader::find(const std::string &name,
                                const bool & caseSensitive)
{
    return m_Root.find(name,caseSensitive);
}

bool XMLReader::exists(const std::string &tagName,
                       const bool &caseSensitive)
{
    return this->getElement(tagName,caseSensitive)?true:false;
}

size_t XMLReader::getNumElements(const std::string &tagName,
                                 const bool & caseSensitive)
{
    const XMLDataElement * element = this->getElement(tagName,caseSensitive);
    if (element)
    {
        return element->getNumChildren();
    }
    std::string errMsg="(FATAL_XMLDataElement::getNumElements) : ";
    errMsg+="Could not find element with tag name equal to \""+tagName+"\"";
    throw InvalidOperationException(errMsg);
}

XMLDataElement *XMLReader::getElement(const std::string &dotNotation,
                                      const bool &caseSensitive)
{
    std::string tag;
    if (caseSensitive)
    {
        tag="ROOT."+dotNotation;
    }
    else
    {
        tag=StringUtils::toUpper("ROOT."+dotNotation);
    }

    std::vector<std::string> items = StringUtils::split(tag,".");
    std::string tagValue;
    XMLDataElement * element=&m_Root;

    if (caseSensitive)
    {
        tagValue=StringUtils::trimmed(dotNotation);
    }
    else
    {
        items[1]=StringUtils::toUpper(items[1]);
        tagValue=StringUtils::trimmed(dotNotation);
        tagValue=StringUtils::toUpper(tagValue);
    }


    if (items[0]==tagValue)
    {
        return element;
    }

    for(unsigned int a1=1;a1<items.size();a1++)
    {
        element = this->getChild(element,items[a1]);
        if (element)
        {
            std::string elementName =
                    StringUtils::toUpper(element->getElementName());
            std::string searchName =
                    StringUtils::toUpper(items[a1]);

            bool isValid = (elementName==searchName);
            if (!isValid)
            {
                return NULL;
            }
        }
        else
        {
            return NULL;
        }
    }

    if (items.size()>0)
    {
        return element;
    }
    return NULL;
}

bool XMLReader::load(const std::string & url)
{
    return loadFromString(FileUtils::getFileContents(url));
}

bool XMLReader::loadFromString(const std::string &data)
{

    this->m_ParseString=data;
    m_Initialized=true;
    this->parse();
    return true;
}

void XMLReader::printToString()
{
    this->m_Depth=0;
    this->printTree(&this->m_Root,this->m_Depth);
}

std::string XMLReader::toString() const
{
    return this->m_ParseString;
}

size_t XMLReader::getNumLines() const
{
    return this->m_LineCount;
}

void XMLReader::processCloseTag()
{
    if (!this->m_Current)
    {
        return;
    }
    this->m_Current = this->m_Current->getParent();
}

void XMLReader::processOpenTag(const std::string &data)
{
    std::vector<std::string> items = StringUtils::split(data," ");
    if (items.size()>0)
    {

            if (!this->m_Current)
            {
                this->m_Current=new XMLDataElement;
                this->m_Root.addChild(this->m_Current);
                this->m_Current->setParent(&this->m_Root);
                this->m_Current->setLocalIndex(this->m_Root.getNumChildren());
                this->m_Current->setElementName(items[0]);
            }
            else
            {
                XMLDataElement * child=new XMLDataElement;
                child->setLocalIndex(this->m_Current->getNumChildren());
                this->m_Current->addChild(child);
                child->setParent(this->m_Current);
                child->setElementName(items[0]);
                this->m_Current=child;
            }
        
        /*Process attributes*/
        //remove tag and get only the attributes        
            StringUtils::trimmed(data.substr(items[0].size(),
                                 data.size()-items[0].size()));
        this->parseAttributes(StringUtils::trimmed(
                                  data.substr(items[0].size(),
                                  data.size()-items[0].size())),
                                  this->m_Current);
    }
}

void XMLReader::printTree(XMLDataElement *element, size_t level)
{
    std::string tag = StringUtils::toUpper(element->getElementName());
    XMLDataElement * searchElement = this->getFirst(this->getRoot(),tag);

    for (size_t a1=0;a1<level;a1++)
    {
        this->m_OutputStream<<"----";
    }
    this->m_OutputStream  <<"-> "
                         <<element->getElementName()
                        <<(searchElement?" YES":" NO")<<"\n";

    level++;
    if (level>this->m_Depth)
    {
        this->m_Depth=level;
    }

    for (size_t a1 = 0;a1<element->getNumChildren();a1++)
    {
        this->printTree(element->getChildAt(a1),level);
    }

}



XMLDataElement *XMLReader::getFirst(XMLDataElement * node,
                                    const std::string name,
                                    const bool &caseSensitive)
{
    std::string tag;
    std::string childName;
    if (caseSensitive)
    {
        tag = node->getElementName();
        childName = name;
    }
    else
    {
        tag = StringUtils::toUpper(node->getElementName());
        childName = StringUtils::toUpper(name);
    }


    if (tag == childName)
    {
        return node;
    }
    else
    {
        size_t childCount  = node->getNumChildren();
        if (childCount == 0)
        {
            node = node->getParent();
            return node;
        }
        else
        {
            return this->getFirst(node->getChildAt(0),
                                  childName,
                                  caseSensitive);
        }
            
    }   
    return NULL;
}

XMLDataElement *XMLReader::getChild(XMLDataElement *parent,
                                    const std::string & childName,
                                    const bool &caseSensitive)
{
    for (size_t a1 = 0;a1<parent->getNumChildren();a1++)
    {
        std::string childTag;
        std::string searchTag;
        if (caseSensitive)
        {
            childTag=childName;
            searchTag=parent->getChildAt(a1)->getElementName();
        }
        else
        {
            childTag = StringUtils::toUpper(childName);
            searchTag =
                    StringUtils::toUpper(parent->getChildAt(a1)->getElementName());
        }

        if (childTag==searchTag)
        {
            return parent->getChildAt(a1);
        }
    }
    return NULL;
}

void XMLReader::parse()
{
    std::string data;
    this->m_Token = this->m_ParseString[this->m_Index];
    this->m_PeekToken = this->m_ParseString[this->m_Index+1];
    while(isParsingValid())
    {
        std::string openTag;
        std::string closeTag;
        if(m_Token=='<' && m_PeekToken=='/')
        {
            this->consume();
            this->consume();
            if (m_Current)
            {
                m_Current->setElementData(StringUtils::trimmed(data));
                data.clear();
            }
            while(this->isParsingValid())
            {
                if (m_Token=='>')
                {
                    break;
                }
                closeTag.push_back(m_Token);
                this->consume();
            }
            this->processCloseTag();
        }
        else if(m_Token=='<' && m_PeekToken=='!')
        {
            while(this->isParsingValid())
            {
                if (m_Token=='>')
                {
                    break;
                }
                this->consume();
            }
        }
        else if (m_Token=='<' && m_PeekToken=='?')
        {
            while(this->isParsingValid())
            {
                if (m_Token=='>')
                {
                    break;
                }
                this->consume();
            }
        }
        else if (m_Token=='<')
        {
            this->consume();
            bool closeTagNeedsProcessing=false;
            size_t quoteCount=0;
            while(this->isParsingValid())
            {
                if (m_Token=='/' && m_PeekToken=='>')
                {
                    closeTagNeedsProcessing=true;
                    break;
                }

                if (m_Token=='\''||m_Token=='"')
                {
                    ++quoteCount;
                }

                if (m_Token=='>' && quoteCount%2==0)
                {
                    break;
                }

                openTag.push_back(m_Token);
                this->consume();
            }
            this->processOpenTag(openTag);
            if (closeTagNeedsProcessing)
            {
                this->processCloseTag();
            }
        }
        else
        {
            data.push_back(m_Token);
        }
        this->consume();
    }
    
}


void XMLReader::parseAttributes(const std::string &attributes,
                                XMLDataElement *element)
{
    if (attributes.length() > 0)
    {
        unsigned int attrCounter=0;
        std::string attributeName;
        std::string attributeValue;
        bool storeName=true;
        bool storeValue=false;
        bool attributeStored=false;
        char valueStopChar=' ';

        while (attrCounter < attributes.length())
        {
            char token = attributes[attrCounter];
            if (token=='\n' || token=='\t' || token=='\r')
            {

            }

            //Parses out the attribute name
            if (storeName)
            {
                while(attrCounter<attributes.size())
                {
                    token = attributes[attrCounter];
                    if (token=='=')
                    {
                        storeName=false;
                        storeValue=true;
                        break;
                    }
                    else
                    {
                        attributeName.push_back(token);
                    }
                    ++attrCounter;
                }

            }


            //parses out the attribute value
            else if (storeValue)
            {

                while(attrCounter<attributes.size())
                {
                    token = attributes[attrCounter];
                    if (token=='\"' || token=='\'')
                    {
                        valueStopChar=token;
                        ++attrCounter;
                        while(attrCounter<attributes.size())
                        {
                            token = attributes[attrCounter];
                            if (token==valueStopChar)
                            {
                                attributeStored=true;
                                break;
                            }
                            attributeValue.push_back(token);
                            ++attrCounter;
                        }

                        break;
                    }
                    ++attrCounter;
                }
            }
            if (attributeStored)
            {

                element->addAttribute(StringUtils::trimmed(attributeName),
                                      StringUtils::trimmed(attributeValue));
                attributeName.clear();
                attributeValue.clear();
                attributeStored=false;
                storeName=true;
                storeValue=false;

            }
            ++attrCounter;
        }
    }
}


void XMLReader::consume()
{

    ++this->m_Index;
    if (this->m_Index >= m_ParseString.length())
    {
        return;
    }
    this->m_Token=m_ParseString[this->m_Index];
    if (this->m_Token =='\n')
    {
        this->m_LineCount++;
        this->m_ColumnCount=0;
    }
    this->m_ColumnCount++;
    if (this->m_Index+1 <m_ParseString.length())
    {
        this->m_PeekToken = m_ParseString[m_Index+1];
    }


}

bool XMLReader::isParsingValid()
{
    return (m_Index<m_ParseString.length());
}

}}}//namespace
