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

#include "utility/inc/XMLUtils.h"
#include "utility/inc/FileUtils.hpp"

#include "contrib/catch/catch.hpp"

#include <sstream>

using namespace cbtek::common::utility;
static const std::string dataFolder = "testData/utility/";


TEST_CASE("Testing XMLReader::getElement","[utility::XMLReader")
{
    std::ostringstream xml;
    xml<<"<xml><element id=\"test\"><element_child value=\"child\"/> </element></xml>";
    std::string tempFile = "temp.xml";
    FileUtils::writeFileContents(tempFile,xml.str());
    XMLReader reader;
    reader.load(tempFile);
    FileUtils::deleteFile(tempFile);
    std::string data = FileUtils::getFileContents(tempFile);
    reader.loadFromString(data);
    const XMLDataElement * root = reader.getElement("XML");
    const XMLDataElement * child = reader.getElement("XML.Element");
    REQUIRE(root!=NULL);
    REQUIRE(child!=NULL);
    REQUIRE(StringUtils::equals(root->getElementName(),"XML"));
    REQUIRE(child->getAttributeValue("id") == "test");

}
