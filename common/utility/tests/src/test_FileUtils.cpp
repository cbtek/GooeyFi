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

#include "utility/inc/StringUtils.hpp"
#include "utility/inc/FileUtils.hpp"
#include "contrib/catch/catch.hpp"

using namespace cbtek::common::utility;
static const std::string dataFolder = "testData/utility/";


TEST_CASE("Testing FileUtils::fileExists","[utility::FileUtils")
{
    std::string data = "The Quick Brown fox\n\t jumped over the moon \t\n";
    FileUtils::writeFileContents("test.tmp",data);
    REQUIRE(FileUtils::fileExists("test.tmp"));
    FileUtils::deleteFile("test.tmp");
}

TEST_CASE("Testing FileUtils::writeFileContents", "[utility::FileUtils]" )
{
    std::string data = "The Quick Brown fox\n\t jumped over the moon \t\n";
    FileUtils::writeFileContents("test.tmp",data);
    std::string dataIn;
    std::ifstream in("test.tmp");
    while (in)
    {
        char token = in.get();
        if (!in)
        {
            break;
        }
        dataIn.push_back(token);
    }
    in.close();
    FileUtils::deleteFile("test.tmp");
    REQUIRE(dataIn == data);
}

TEST_CASE("Testing FileUtils::copy", "[utility::FileUtils]" )
{
    std::string data = "The Quick Brown fox\n\t jumped over the moon \t\n";
    FileUtils::writeFileContents("test.tmp",data);
    FileUtils::copyFile("test.tmp","test-copy.tmp");

    REQUIRE(FileUtils::fileExists("test-copy.tmp"));

    std::string dataIn;
    std::ifstream in("test-copy.tmp");
    while (in)
    {
        char token = in.get();
        if (!in)
        {
            break;
        }
        dataIn.push_back(token);
    }
    in.close();
    FileUtils::deleteFile("test.tmp");
    FileUtils::deleteFile("test-copy.tmp");
    REQUIRE(dataIn == data);
}
