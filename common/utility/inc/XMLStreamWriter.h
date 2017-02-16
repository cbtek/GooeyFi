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
#ifndef _CBTEK_COMMON_UTILITY_XMLSTREAMWRITER_H
#define _CBTEK_COMMON_UTILITY_XMLSTREAMWRITER_H
#include <ostream>

namespace cbtek {
namespace common {
namespace utility {

class XMLStreamWriter 
{
	public:
	//! Constructor for XMLStreamWriter	
    XMLStreamWriter(std::ostream & out);

    /**
     * @brief writeStartDocument
     * @param version
     * @param flag
     */
    void writeStartDocument(const std::string & version="1.0", bool flag=true);

    /**
     * @brief writeStartElementNoAttributes
     * @param tag
     */
    void writeStartElementNoAttributes(const std::string & tag);

    /**
     * @brief writeStartElement
     * @param tag
     */
    void writeStartElement(const std::string & tag);

    /**
     * @brief writeEndElement
     */
    void writeEndElement();

    /**
     * @brief writeEndElement
     * @param tag
     */
    void writeEndElement(const std::string &tag);

    /**
     * @brief writeTextElement
     * @param tag
     * @param text
     */
    void writeTextElement(const std::string & tag, const std::string & text);    

    /**
     * @brief writeAttribute
     * @param attributeName
     * @param attributeValue
     */
    void writeAttribute(const std::string & attributeName, const std::string & attributeValue);    
	//! Destructor
	~XMLStreamWriter();	

private:
    void writeTabs();
    std::string m_currentNS;
    size_t m_currentTab;
    std::ostream & m_out;
};
}}}//end namespace

#endif

