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

#ifndef _CBTEK_COMMON_UTILITY_XMLREADER_H
#define _CBTEK_COMMON_UTILITY_XMLREADER_H

#include <sstream>
#include <fstream>

#include "XMLDataElement.h"
#include "UtilityCommon.hpp"

namespace cbtek {
namespace common {
namespace utility {

class CBTEK_UTILS_DLL XMLReader
{

public:
    XMLReader();
    ~XMLReader();
    /**
     * @brief load
     * @param filename
     * @return
     */
    bool load(const std::string & filename);

    /**
     * @brief loadFromString
     * @param data
     * @return
     */
    bool loadFromString(const std::string & data);

    /**
     * @brief getElement
     * @param tagName
     * @param caseSensitive
     * @return
     */
    XMLDataElement * getElement(const std::string & tagName,
                                const bool & caseSensitive=false);

    /**
     * @brief find
     * @param name
     * @param caseSensitive
     * @return
     */
    XMLDataElement * find(const std::string & name,
                          const bool & caseSensitive=false);

    /**
     * @brief getNumElements
     * @param tagName
     * @param caseSensitive
     * @return
     */
    size_t  getNumElements(const std::string & tagName,
                           const bool & caseSensitive=false);


    /**
     * @brief exists
     * @param tagName
     * @param caseSensitive
     * @return
     */
    bool exists(const std::string & tagName,
                const bool & caseSensitive=false);

    /**
     * @brief toString
     * @return
     */
    std::string toString()const;

    /**
     * @brief getRoot
     * @return
     */
    XMLDataElement * getRoot();

    /**
     * @brief getRoot
     * @return
     */
    const XMLDataElement *getRoot() const;

    /**
     * @brief isValid
     * @return
     */
    bool isValid()const;

    /**
     * @brief getDepth
     * @return
     */
    size_t getDepth()const;

    /**
     * @brief getNumLines
     * @return
     */
    size_t getNumLines()const;

    /**
     * @brief reset
     */
    void reset();

    /**
     * @brief clear
     */
    void clear();

    /**
     * @brief getFirstElement
     * @return
     */
    XMLDataElement *getFirstElement();
private:

    void printToString();
    void parse();
    void sync();
    void parseAttributes(const std::string & attributes, XMLDataElement * element);
    void consume();
    bool isParsingValid();
    char m_Token;
    char m_PeekToken;
    void processCloseTag();
    void processOpenTag(const std::string & data);
    void printTree(XMLDataElement * element, size_t level);
    XMLDataElement * getFirst(XMLDataElement *node,
                              const std::string name,
                              const bool & caseSensitive=false);

    XMLDataElement * getChild(XMLDataElement * parent,
                              const std::string &childName,
                              const bool & caseSensitive=false);
    

    bool m_Initialized;
    size_t m_Depth;
    size_t m_Index;
    size_t m_LineCount;
    size_t m_ColumnCount;

    #ifdef _MSC_VER
    #   pragma warning( push )
    #   pragma warning( disable : 4251 )
    #endif
        XMLDataElement m_Root;
        XMLDataElement * m_Current;
        std::string m_ParseString;
        std::ostringstream m_OutputStream;         
    #ifdef _MSC_VER
    #   pragma warning( pop )
    #endif          
};
}}}//namespace
#endif // XMLREADER_H
