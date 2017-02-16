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


#ifndef _CBTEK_COMMON_UTILITY_STRING_UTILS_HPP_
#define _CBTEK_COMMON_UTILITY_STRING_UTILS_HPP_

#include "utility/inc/Exception.hpp"
#include "utility/inc/UtilityCommon.hpp"
#include "utility/inc/Random.h"
#include "utility/inc/TimeUtils.hpp"
#include "utility/inc/ObjectList.hpp"

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>


namespace cbtek {
namespace common {
namespace utility {
namespace StringUtils {

/**
* @brief Converts wide string to upper-case
* @param Reference to the wide string to convert
*/
inline void toUpperInPlace(std::wstring &str)
{
    size_t count=str.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        str[a1] = towupper(str[a1]);
    }
}

/**
* @brief Converts wide string to lower-case
* @param inputString Reference to the wide string to convert
*/
inline void toLowerInPlace(std::wstring &str)
{
    size_t count=str.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        str[a1] = towlower(str[a1]);
    }
}

/**
* @brief Converts string to upper-case
* @param Reference to the string to convert
*/
inline void toUpperInPlace(std::string &str)
{
    size_t count=str.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        str[a1] = static_cast<char>(toupper(str[a1]));
    }
}

/**
* @brief Converts string to lower-case
* @param Reference to the string to convert
*/
inline void toLowerInPlace(std::string &str)
{
    size_t count=str.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        str[a1] = static_cast<char>(tolower(str[a1]));
    }
}

/**
* @brief Converts string to upper-case
* @param The string to convert
* @return The converted string
*/
inline std::string toUpper(const std::string &str)
{
    std::string strOut = str;
    toUpperInPlace(strOut);
    return strOut;
}

/**
* @brief Converts wide string to lower-case
* @param The string to convert
* @return The converted string
*/
inline std::string toLower(const std::string &str)
{
    std::string strOut = str;
    toLowerInPlace(strOut);
    return strOut;
}
/**
 * @brief The CaseInsensitiveEqual struct
 *
 */
template<typename T>
struct CaseInsensitiveEqual
{
    explicit CaseInsensitiveEqual (const T & str) : m_str(str){}

    inline bool operator()(const T & strIn)
    {
        return toLower(m_str) == toLower(strIn);
    }
private:
    T m_str;
};
typedef CaseInsensitiveEqual<std::string> CaseInsensitiveStringEqual;
typedef CaseInsensitiveEqual<std::wstring> CaseInsensitiveWideStringEqual;

/**
* @brief Remove all instances of a substring from a string
* @param The string to remove characters from
* @param The actual string to remove
* @param Case sensitivity
* @return Number of removes
*/
inline size_t removeInPlace(std::string &srcString,
                            const std::string &stringToRemove,
                            bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t removeCount=0;
    if (caseSensitive)
    {
        std::string::size_type i = srcString.find(stringToRemove);

         while (i != std::string::npos)
        {
           srcString.erase(i, stringToRemove.length());
           ++removeCount;
           i = srcString.find(stringToRemove);

        }
    }
    else
    {

        std::string srcStringUpper = toUpper(srcString);
        std::string stringToRemoveUpper = toUpper(stringToRemove);
        std::string::size_type i = srcStringUpper.find(stringToRemoveUpper);

        while (i != std::string::npos)
        {
           srcString.erase(i, stringToRemove.length());
           ++removeCount;
           i = srcStringUpper.find(stringToRemoveUpper);
        }
    }
    return removeCount;
}

/**
 * @brief toHexString
 * @param value
 * @return
 */
template <typename T>
inline std::string toHexString(T value)
{
    std::ostringstream hex;
    hex << std::hex << value;
    std::string hexStr=hex.str();
    return hexStr;
}

/**
 * @brief Returns a bitstring representing template value
 * @param value
 * @param byteSep
 * @param wordSep
 * @return
 */
template <typename T>
inline std::string toBitString(T value,
                               const std::string & byteSep="",
                               const std::string & wordSep="")
{

        std::ostringstream hex,out;
        hex << std::hex << value;
        std::string hexStr=hex.str();
        removeInPlace(hexStr,"0x");
        toUpperInPlace(hexStr);
        std::map<char,std::string> hexMap;
        hexMap['0']="0000";
        hexMap['1']="0001";
        hexMap['2']="0010";
        hexMap['3']="0011";
        hexMap['4']="0100";
        hexMap['5']="0101";
        hexMap['6']="0110";
        hexMap['7']="0111";
        hexMap['8']="1000";
        hexMap['9']="1001";
        hexMap['A']="1010";
        hexMap['B']="1011";
        hexMap['C']="1100";
        hexMap['D']="1101";
        hexMap['E']="1110";
        hexMap['F']="1111";

        int wordCount=0;
        for (size_t a1 = 0;a1<hexStr.size();++a1)
        {
            out<<hexMap[hexStr[a1]];
            if (wordCount==1)
            {
                out << byteSep;
                wordCount=0;
            }
            else if (a1<hexStr.size()-1)
            {
                out << wordSep;
            }

        }
    return out.str();
}

template<typename T>
inline T toNumber(const std::string & value)
{
    std::istringstream in(value,std::istringstream::in);
    T returnValue;
    in>>returnValue;
    return returnValue;
}

/**
 * @brief Prints vector of templated type if underlying type
 *        supports it.
 * @param out The stream to write to
 * @param values The values to print
 */
template <typename T>
inline void printVector(std::ostream & out,
                        const std::vector<T> & values)
{
    size_t count = values.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        out <<"["<<a1<<"] = "<< values[a1]<<std::endl;
    }
}


/**
 * @brief toString
 * @param value
 * @return
 */
template <typename T>
inline std::string toString(T value)
{
    std::ostringstream out;
    out << value;
    return out.str();
}

/**
 * @brief Perfroms string replace (in-place)
 * @param inputString Reference to the inputString to perform
 * in-place replacement
 * @param oldString The old string to replace
 * @param newString The new string to insert
 * @param isCaseSensitive Should oldString be caseSensitive
 * within inputString?
 */
inline void replaceInPlace(std::string &inputString,
                                 const std::string &oldString,
                                 const std::string &newString,
                                 bool isCaseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    if (isCaseSensitive)
    {
        size_t pos = 0;
        while((pos = inputString.find(oldString, pos)) != std::string::npos)
        {
             inputString.replace(pos, oldString.length(), newString);
             pos += newString.length();
        }
    }
    else
    {
        std::string subject = toUpper(inputString);
        std::string search  = toUpper(oldString);
        std::string replace = toUpper(newString);
        size_t pos = 0;
        while((pos = subject.find(search, pos)) != std::string::npos)
        {
             inputString.replace(pos, search.length(), newString);
             pos += newString.length();
        }
    }
}

/**
 * @brief Perfroms string replace (in-place)
 * @param inputString The string that contains oldString to replace
 * @param oldString The old string to replace
 * @param newString The new string to insert
 * @param isCaseSensitive Should oldString be caseSensitive
 * within inputString?
 * @return inputString with the replaced oldString.  If oldString
 * is not found within inputString then inputString is returned
 * unmodified.
 */
inline std::string replace(const std::string &inputString,
                                 const std::string &oldString,
                                 const std::string &newString,
                                 bool isCaseSensitive = c_DEFAULT_CASE_SENSITIVE)
{

    if (isCaseSensitive)
    {
        std::string subject = inputString;
        std::string search  = oldString;
        std::string replace = newString;

            size_t pos = 0;
            while((pos = subject.find(search, pos)) != std::string::npos)
            {
                 subject.replace(pos, search.length(), replace);
                 pos += replace.length();
            }
            return subject;
    }
    else
    {
        std::string subject = (inputString);
        std::string search  = toUpper(oldString);
        std::string replace = toUpper(newString);

            size_t pos = 0;
            while((pos = subject.find(search, pos)) != std::string::npos)
            {
                 subject.replace(pos, search.length(), replace);
                 pos += replace.length();
            }
            return subject;
    }
}

//##############################################
// TRIM FUNCTIONS
//##############################################

/**
* @brief Converts wide string to upper-case
* @param The string to convert
* @return The converted string
*/
inline std::wstring toUpper(const std::wstring &str)
{
    std::wstring strOut = str;
    toUpperInPlace(strOut);
    return strOut;
}

/**
* @brief Converts wide string to lower-case
* @param The string to convert
* @return The converted string
*/
inline std::wstring toLower(const std::wstring &str)
{
    std::wstring strOut = str;
    toLowerInPlace(strOut);
    return strOut;
}


/**
* @brief Removes all whitespace (\t \r \n ' ' \f) from
*        the beginning and end of inputString.
* @param Reference to the source string to operate upon
*/
inline void trimmedInPlace(std::string &str)
{
    int count=static_cast<int>(str.size());
    for (int a1 = 0;a1<count;++a1)
    {
        if (str[a1]==' '||
            str[a1]=='\n' ||
            str[a1]=='\r' ||
            str[a1]=='\f' ||
            str[a1]=='\t' )
        {
            str.erase(str.begin()+a1);
            a1--;
            count--;
            continue;
        }
        else break;
    }


    if (count==0)
    {
        return;
    }
    int cnt = static_cast<int>(count);
    for (int a1 = cnt-1;a1 >= 0;--a1)
    {
        if (str[a1]==' '||
            str[a1]=='\n' ||
            str[a1]=='\r' ||
            str[a1]=='\f' ||
            str[a1]=='\t' )
        {
            str.erase(str.begin()+a1);
        }
        else
        {
            break;
        }
    }
}

/**
* @brief Removes all whitespace (\t \r \n ' ' \f) from
*        the beginning and end of inputString.
* @param The source string to operate upon
* @return Returns the trimmed string as a copy.
*
*/
inline std::string trimmed(const std::string &str)
{
    std::string strOut = str;
    trimmedInPlace(strOut);
    return strOut;
}


/**
* @brief Converts wide string to upper-case and then trims it
* @param input The string to convert
* @return The converted string
*/
inline std::string toUpperTrimmed(const std::string &inputString)
{
    return trimmed(toUpper(inputString));
}

/**
* @brief Converts wide string to lower-case and then trims it
* @param input The string to convert
* @return The converted string
*/
inline std::string toLowerTrimmed(const std::string &inputString)
{
    return trimmed(toLower(inputString));
}

/**
* @brief Determines if two (case-insensitive) strings are equal
* @param inputString1 The first string
* @param inputString2 The second string
* @return True if case-insensitve match occurs, false otherwise
*/
inline bool equals(const std::string &str1,
                         const std::string &str2)
{
    return (toUpper(str1) == toUpper(str2));
}

/**
* @brief Splits a string based on the delimeter
* @param inputString The string to split
* @param delimiter The delimiter used to break the string apart
* @param splitItems Reference to string vector. Avoids vector copy.
* @code {.cpp}
    //Example: Split string based on custom delim

    std::string line = "test|item <$CBTEK$> test,data";

    std::vector<std::string>items;

    split(line,"<$CBTEK$>",items);

    //Example Results:
    //items[0]="test|item";
    //items[1]="test,data";
    @endcode
*/
inline void split(const std::string &str,
                  const std::string &delimiter,
                  std::vector<std::string> &splitItems)
{
    std::string s = str;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        splitItems.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    splitItems.push_back(s);
}


/**
* @brief Splits a string based on the delimeter
* @param inputString The string to split
* @param delimiter The delimiter used to break the string apart
* @return Return a vector of split strings
* @code {.cpp}
    //Example: Split string based on custom delim

    std::string line = test|item <$CBTEK$> test,data

    std::vector<std::string>items;

    items = split(line,"<$CBTEK$>");

    //Example Results:
    //items[0]="test|item";
    //items[1]="test,data";
    @endcode
*/
inline std::vector<std::string> split(const std::string &str,
                                      const std::string &delimiter)
{
    std::vector<std::string> outItems;
    split(str,delimiter,outItems);
    return outItems;
}

/**
* @brief Parses the command line arguments and adds
*        values to vector of strings
* @param argc The argument count from main
* @param argv The argument array from main
* @param argsOut Reference to a vector of strings to
*        hold arguments. Avoids vector copy.
*/
inline void parseCommandLineArgs(int argc,
                                 char **argv,
                                 std::vector<std::string> &argsOut)
{
    if (argc > 0)
    {
        argsOut.assign(argv,argv+argc);
    }
}

/**
* @brief Parses command line args and returns
*        value for argument.
* @param argc The argc argument count from main
* @param argv The argv argument array from main
* @param argName The argName argument name to find
* @param altArgName The altArgName alternative name to find
* @return The value for the argument name.
*         Returns empty string if arg name
*         is not located.
*
*/
inline std::string getCommandLineArg(int argc, char **argv,
                                     const std::string &argName,
                                     const std::string &altArgName="")
{
    std::vector<std::string> args;
    parseCommandLineArgs(argc,argv,args);
    size_t argCount = args.size();
    for (size_t a1 = 0;a1<argCount;++a1)
    {
        if ((args[a1]==argName || args[a1]==altArgName) && (a1+1) < argCount)
        {
            return args[a1+1];
        }
    }
    return "";

}

/**
 * @brief contains
 * @param src
 * @param subStr
 * @param caseSensitive
 * @return
 */
inline bool contains(const std::string &srcStr,
                     const std::string &subStr,
                     bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    if (caseSensitive)
    {
        if (srcStr.find(subStr) != std::string::npos)
        {
            return true;
        }
    }
    else
    {
        if (toUpper(srcStr).find(toUpper(subStr)) !=
                std::string::npos)
        {
            return true;
        }
    }
    return false;
}


/**
 * @brief contains
 * @param values
 * @param subString
 * @param caseSensitive
 * @return
 */
inline bool contains(const std::vector<std::string> & values,
                     const std::string & subString,
                     bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    for (size_t a1 = 0; a1 < values.size(); ++a1)
    {
        bool value = StringUtils::contains(values[a1],subString,caseSensitive);
        if (value)
        {
            return true;
        }
    }
    return false;
}



/**
 * @brief contains
 * @param values
 * @param subString
 * @param caseSensitive
 * @return
 */
inline bool contains(const std::string & value,
                     const std::vector<std::string> & subStrings,
                     bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    for (size_t a1 = 0; a1 < subStrings.size(); ++a1)
    {
        bool exists = StringUtils::contains(value,subStrings[a1],caseSensitive);
        if (exists)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief commandLineArgExists
 * @param argc
 * @param argv
 * @param argName
 * @return
 */
inline bool commandLineArgExists(int argc,
                                 char ** argv,
                                 const std::string &argName)
{
    std::vector<std::string> args;
    parseCommandLineArgs(argc,argv,args);
    return(StringUtils::contains(args,argName));
}

/**
* @brief This function joins together all items in vector
* @param items Vector of items to join together
* @return Concatenated string of all the contents
*  of this StringList
*/
inline std::string join(const std::vector<std::string> & items)
{
    std::stringstream out;
    size_t count = items.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        out << items[a1];
    }
    return out.str();
}

/**
* @brief toString
* @param seperator Seperator string to insert between each item in
* the StringList
* @param items Vector of items to join together
* @return Concatenated string of all the contents
* seperated by "seperator" string
*/
inline std::string join(const std::string &seperator,
                        const std::vector<std::string> & items)
{
    std::stringstream out;
    size_t count = items.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        out << items[a1]<<((a1<count-1)?seperator:"");
    }
    return out.str();
}


/**
* @brief toString
* @param seperator Seperator string to insert between each item in
* the StringList
* @param prefix Prefix string that is inserted before each item in
* the StringList
* @param postfix Postfix string that is inserted after each item in
* the StringList
* @param items Vector of items to join together
* @return Concatenated string of all the contents
* seperated by "seperator" string and surrounded by
* "prefix" and "postfix" strings
*/
inline std::string join(const std::string &seperator,
                        const std::string &prefix,
                        const std::string &postfix,
                        const std::vector<std::string> & items)
{
    std::stringstream out;
    size_t count = items.size();
    for (size_t a1 = 0;a1<count;++a1)
    {
        out << prefix<<items[a1]<<postfix<<((a1<count-1)?seperator:"");
    }
    return out.str();
}

/**
* @brief Returns the index of the given inputString
* @param inputString The string to search
* @param Vector of items to search
* @param caseSensitive Case sensitivity of the inputString
* @return
*/
inline size_t indexOf(const std::string &str,
                      const std::vector<std::string> & items,
                      bool isCaseSensitive)
{
    if (items.size() == 0)
    {

        throw InvalidOperationException(EXCEPTION_TAG+"Exception is being thrown because of an empty items vector!");
    }
    std::vector<std::string>::const_iterator it;
    std::vector<std::string>::const_iterator itStart=items.begin();
    std::vector<std::string>::const_iterator itEnd=items.end();

    if (isCaseSensitive)
    {
        it = std::find(itStart,itEnd,str);
    }
    else
    {
        it = std::find_if(itStart,itEnd,CaseInsensitiveStringEqual(str));
    }
    size_t ndx = std::distance(itStart,it);

    if (ndx < items.size())
    {
        return ndx;
    }
    int count=0;
    std::string msg=EXCEPTION_TAG+"The string \""+str+"\" was not found in this collection:";
    for (std::string item : items)
    {
        msg+="\n\t["+StringUtils::toString(count)+"]="+item;
        ++count;
    }
    throw InvalidOperationException(msg);
}

/**
* @brief Converts floating point values to "x.xxxx" form
* @param floatValue Floating point value
* @param digitsAfterDecimal Number of digits to include after decimal
* @return string of converted floating point value
*/
inline std::string toString(double floatValue,
                            int digitsAfterDecimal)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(digitsAfterDecimal) << floatValue;
    return stream.str();
}

/**
* @brief Find value and return all text after it(exclusive)
* @param inputString The string to copy and operate upon
* @param value The string to look for
* @param isCaseSensitive Should value be case sensitive?
* @return The text found after value
*/
inline std::string textAfter(const std::string &src,
                             const std::string &value,
                             bool  isCaseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    std::string str=src;
    std::string v1=value;
    if (!isCaseSensitive)
    {
        str=toUpper(str);
        v1=toUpper(v1);
    }

    size_t start = str.find(v1);
    if (start==std::string::npos)
    {
        return "";
    }

    start=start+v1.size();
    size_t len=str.size()-v1.size();
    return src.substr(start,len);
}


/**
* @brief Find value and return all text before it(exclusive)
* @param inputString The string to copy and operate upon
* @param value The string to look for
* @param isCaseSensitive Should value be case sensitive?
* @return The text found before value
*/
inline std::string textBefore(const std::string &src,
                             const std::string &value,
                             bool  isCaseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    std::string str=src;
    std::string v1=value;
    if (!isCaseSensitive)
    {
        str=toUpper(str);
        v1=toUpper(v1);
    }

    size_t len = str.find(v1);
    if (len == std::string::npos)
    {
        return "";
    }
    return src.substr(0,len);
}

/**
* @brief repeat
* @param value
* @param repeatCount
* @return string that gets repeated
*/
inline std::string repeat(const std::string &value,
                          const size_t &repeatCount)
{
    std::string returnStr;
    for (size_t a1 = 0;a1<repeatCount;++a1)
    {
        returnStr+=value;
    }
    return returnStr;
}


/**
* @brief repeat
* @param value
* @param returnStr
* @param repeatCount
*/
inline void repeat(const std::string &value,
                   std::string & returnStr,
                   const size_t &repeatCount)
{
    for (size_t a1 = 0;a1<repeatCount;++a1)
    {
        returnStr+=value;
    }
}


/**
 * @brief remove
 * @param srcString
 * @param stringToRemove
 * @param caseSensitive
 * @return
 */
inline std::string remove(const std::string &srcString,
                          const std::string &stringToRemove,
                          bool caseSensitive=c_DEFAULT_CASE_SENSITIVE)
{
    std::string source = srcString;
    removeInPlace(source,stringToRemove,caseSensitive);
    return source;
}

/**
 * @brief toUInt
 * @param UIntStr
 * @return
 */
inline std::uint64_t toUInt(const std::string &UIntStr)
{
    return toNumber<std::uint64_t>(UIntStr);
}

/**
 * @brief toInt
 * @param intStr
 * @return
 */
inline std::int64_t toInt(const std::string &intStr)
{
    return toNumber<std::int64_t>(intStr);
}

/**
 * @brief toFloat64
 * @param f64Str
 * @return
 */
inline double toFloat64(const std::string &f64Str)
{
   return toNumber<double>(f64Str);
}

/**
 * @brief toFloat32
 * @param f32Str
 * @return
 */
inline float toFloat32(const std::string &f32Str)
{
    return toNumber<float>(f32Str);
}

/**
 * @brief isFloat
 * @param floatString
 * @return
 */
inline bool isFloat(const std::string &floatString)
{
    std::istringstream iss(floatString);
    double f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();

}


/**
* @brief Determines if inputString starts with value
* @param inputString The source input string
* @param startsWithValue The value that inputString startsWith
* @param isCaseSensitive Should startsWithValue be case sensitive?
* @return true if inputString starts with startsValue, else false
*/
inline bool startsWith(const std::string &inputString,
                       const std::string &startsWithValue,
                       bool isCaseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    if(inputString.size()<startsWithValue.size())
    {
        return false;
    }

    if (isCaseSensitive)
    {
        return !inputString.compare(0, startsWithValue.size(), startsWithValue);
    }
    else
    {
        std::string str1=toLower(inputString);
        std::string str2=toLower(startsWithValue);
        return !str1.compare(0, str2.size(), str2);
    }
}

/**
* @brief endsWith
* @param src
* @param value
* @param caseSensitive
* @return
*/
inline bool endsWith(const std::string &src,
                     const std::string &value,
                     bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    if(src.size()<value.size())
    {
       return false;
    }
    if (caseSensitive)
    {
       return !src.compare(src.size() - value.size(), value.size(), value);
    }
    else
    {
       std::string srcLower=toLower(src);
       std::string valueLower = toLower(value);
       return !srcLower.compare(srcLower.size() - valueLower.size(), valueLower.size(), valueLower);
    }
}


/**
 * @brief endsWithMultiple
 * @param src
 * @param values
 * @param caseSensitive
 * @return
 */
inline bool endsWithMultiple(const std::string & src,
                             const std::vector<std::string> & values,
                             bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    for(const std::string & item : values)
    {
        if (endsWith(src,item,caseSensitive))
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief itemInVectorEndsWith
 * @param src
 * @param values
 * @param caseSensitive
 * @return
 */
inline size_t itemInVectorEndsWith(const std::string &src,
                                   const std::vector<std::string> &values,
                                   bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t count = values.size();
    if (caseSensitive)
    {
        std::string srcUpper = toUpper(src);
        for (size_t a1 = 0;a1<count;++a1)
        {
            bool flag = endsWith(srcUpper,toUpper(values[a1]));
            if (flag)return a1;
        }
    }
    else
    {
        for (size_t a1 = 0;a1<count;++a1)
        {
            bool flag = endsWith(src,(values[a1]));
            if (flag)return a1;
        }
    }
    return std::string::npos;
}


/**
 * @brief eraseFromVector
 * @param vectorSrc
 * @param itemToErase
 * @param caseSensitive
 */
inline void eraseFromVector(std::vector<std::string> &vectorSrc,
                            const std::string &itemToErase,
                            bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    if (caseSensitive)
    {
        std::string value = itemToErase;
        int count = static_cast<int>(vectorSrc.size());
        for (int a1  = count-1;a1 >=0;--a1)
        {
            if (value==vectorSrc[a1])
            {
                vectorSrc.erase(vectorSrc.begin()+a1);
            }
        }
    }
    else
    {
        std::string value = toUpper(itemToErase);
        int count = static_cast<int>(vectorSrc.size());
        for (int a1  = count-1;a1>=0;--a1)
        {
            if (value==toUpper(vectorSrc[a1]))
            {
                vectorSrc.erase(vectorSrc.begin()+a1);
            }
        }
    }
}



/**
 * @brief findAllThatStartWith
 * @param items
 * @param startsWithValue
 * @param itemsOut
 * @param isCaseSensitive
 */
inline void findAllThatStartWith(const std::vector<std::string> &items,
                                 const std::string &startsWithValue,
                                 std::vector<std::string> &itemsOut,
                                 bool isCaseSensitive=true)
{
    for (size_t a1 = 0; a1 < items.size(); ++a1)
    {
        if (startsWith(items[a1],startsWithValue,isCaseSensitive))
        {
            itemsOut.push_back(items[a1]);
        }
    }
}

/**
 * @brief findAllThatEndWith
 * @param items
 * @param startsWithValue
 * @param itemsOut
 * @param isCaseSensitive
 */
inline void findAllThatEndWith(const std::vector<std::string> &items,
                        const std::string &endsWithValue,
                        std::vector<std::string> &itemsOut,
                        bool isCaseSensitive=true)
{
    for (size_t a1 = 0; a1 < items.size(); ++a1)
    {
        if (endsWith(items[a1],endsWithValue,isCaseSensitive))
        {
            itemsOut.push_back(items[a1]);
        }
    }
}

/**
 * @brief findAllThatContain
 * @param items
 * @param startsWithValue
 * @param itemsOut
 * @param isCaseSensitive
 */
inline void findAllThatContain(const std::vector<std::string> &items,
                               const std::string &containsValue,
                               std::vector<std::string> &itemsOut,
                               bool isCaseSensitive=true)
{
    for (size_t a1 = 0; a1 < items.size(); ++a1)
    {
        if (contains(items[a1],containsValue,isCaseSensitive))
        {
            itemsOut.push_back(items[a1]);
        }
    }
}






/**
* @brief Find and return all text between firstValue and lastValue (exclusive)
* @param inputString The string to copy and operate upon
* @param firstValue The begin string to find
* @param lastValue The end string value
* @param isCaseSensitive Should firstValue and lastValue be case sensitive?
* @return The text found between first and last.  Empty string
* is returned if both first and last are not found.
*/
inline std::string textBetween(const std::string &source,
                               const std::string &firstValue,
                               const std::string &lastValue,
                               bool  isCaseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    std::string str=source;
    std::string v1=firstValue;
    std::string v2=lastValue;
    if (!isCaseSensitive)
    {
        str=toUpper(str);
        v1=toUpper(v1);
        v2=toUpper(v2);
    }

    size_t start = str.find(v1);
    size_t end   = str.find(v2, start+v1.length());    
    if(start == std::string::npos || end == std::string::npos)
    {
        return "";
    }
    return source.substr(start+v1.length(), end - (start+v1.length()));
}

/**
 * @brief Trims all items and removes empty elements
 * @param items
 */
inline void clean(std::vector<std::string> & items)
{
    for (int a1 = items.size()-1; a1>=0 ;--a1)
    {
        if (items[a1].empty())
        {
            items.erase(items.begin()+a1);
            continue;
        }
        StringUtils::trimmedInPlace(items[a1]);
    }
}

inline std::string createUUID(bool includeDashes)
{

    //123e4567-e89b-12d3-a456-426655440000

    Random rnd;
    rnd.reseed((std::uint64_t)TimeUtils::getMillisecondsNow() + TimeUtils::getSecondsNow());

    std::string uuid;

    for (size_t a1 = 0;a1<20;++a1)
    {
        if (rnd.next(100) > 50)
        {
            uuid.push_back(rnd.next('A','F'));
        }
        else
        {
            uuid.push_back(rnd.next('0','9'));
        }
    }

    std::string timeStr = StringUtils::toString(((std::uint64_t)TimeUtils::getMillisecondsNow()));
    if (timeStr.size()>12)
    {
        timeStr=timeStr.substr(0,12);
    }
    else
    {
        for (size_t a1 = timeStr.size(); a1<12;++a1)
        {
            timeStr.push_back('0');
        }
    }
    uuid+=timeStr;
    if (includeDashes)
    {

        uuid.insert(20,"-");
        uuid.insert(16,"-");
        uuid.insert(12,"-");
        uuid.insert(8,"-");
    }

    return uuid;
}

inline std::vector<size_t> getWholeWords(const std::string & source, const std::string & word)
{
    std::vector<size_t> wholeWords;

    auto index = source.find(word,0);
    while(index != std::string::npos)
    {
        bool backIsAlphaNum = false;
        bool frontIsAlphaNum = false;
        if (index + word.size() < source.size() && std::isalnum(source[index+word.size()]))
        {
            backIsAlphaNum = true;
        }

        if (index > 0 && std::isalnum(source[index-1]))
        {
            frontIsAlphaNum = true;
        }
        if (!backIsAlphaNum && !frontIsAlphaNum)
        {
            wholeWords.push_back(index);
        }
        index = source.find(word,index+1);
    }
    return wholeWords;
}

inline UInt64List serializeToIntegerList(const std::string &str)
{
    UInt64List serialized;
    for (size_t a1 = 0;a1< str.size();++a1)
    {
        serialized << (int)str[a1];
    }
    return serialized;
}


inline bool isUnsignedInteger(const std::string &str)
{
    for (size_t a1 = 0;a1<str.length();++a1)
    {
        if (std::isalpha(str[a1])  || str[a1]=='.' )
        {
            return false;
        }
    }

    return true;
}

inline bool isSignedInteger(const std::string &str)
{
    for (size_t a1 = 0;a1<str.length();++a1)
    {
        if (std::isalpha(str[a1]) || str[a1]=='.')
        {
            if (str[a1]=='-')
            {
                continue;
            }
            return false;
        }
    }

    return true;
}


inline bool vectorContains(const std::vector<std::string> & vecIn,
                           const std::string & strIn,
                           bool caseSensitive=true)
{
    for (const auto & value : vecIn)
    {
        if (StringUtils::contains(value,strIn,caseSensitive))
        {
            return true;
        }
    }
    return false;
}

inline size_t removeAllThatDoNotEndWith(std::vector<std::string> & vecOut,
                                        const std::string & strToRemove,
                                        bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t totalRemoved = 0;
    int count = vecOut.size();
    if (count == 0 )
    {
        return 0;
    }

    for (int a1 = count-1;a1 >= 0; --a1)
    {
            if (!StringUtils::endsWith(vecOut[a1],strToRemove,caseSensitive))
            {
                vecOut.erase(vecOut.begin()+a1);
                ++totalRemoved;
            }
    }
    return totalRemoved;
}

inline size_t removeAllThatEndWith(std::vector<std::string> & vecOut,
                            const std::string & strToRemove,
                            bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t totalRemoved = 0;
    int count = vecOut.size();
    if (count == 0 )
    {
        return 0;
    }

    for (int a1 = count-1;a1 >= 0; --a1)
    {
            if (StringUtils::endsWith(vecOut[a1],strToRemove,caseSensitive))
            {
                vecOut.erase(vecOut.begin()+a1);
                ++totalRemoved;
            }
    }
    return totalRemoved;
}

inline size_t removeAllThatStartWith(std::vector<std::string> & vecOut,
                            const std::string & strToRemove,
                            bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t totalRemoved = 0;
    int count = vecOut.size();
    if (count == 0 )
    {
        return 0;
    }

    for (int a1 = count-1;a1 >= 0; --a1)
    {
            if (StringUtils::startsWith(vecOut[a1],strToRemove,caseSensitive))
            {
                vecOut.erase(vecOut.begin()+a1);
                ++totalRemoved;
            }
    }
    return totalRemoved;
}

inline size_t removeAllThatDoNotStartWith(std::vector<std::string> & vecOut,
                                          const std::string & strToRemove,
                                          bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t totalRemoved = 0;
    int count = vecOut.size();
    if (count == 0 )
    {
        return 0;
    }

    for (int a1 = count-1;a1 >= 0; --a1)
    {
            if (!StringUtils::startsWith(vecOut[a1],strToRemove,caseSensitive))
            {
                vecOut.erase(vecOut.begin()+a1);
                ++totalRemoved;
            }
    }
    return totalRemoved;
}

inline size_t removeAllThatContain(std::vector<std::string> & vecOut,
                            const std::string & strToRemove,
                            bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t totalRemoved = 0;
    int count = vecOut.size();
    if (count == 0 )
    {
        return 0;
    }

    for (int a1 = count-1;a1 >= 0; --a1)
    {
            if (StringUtils::contains(vecOut[a1],strToRemove,caseSensitive))
            {
                vecOut.erase(vecOut.begin()+a1);
                ++totalRemoved;
            }
    }
    return totalRemoved;
}


inline size_t removeAllThatDoNotContain(std::vector<std::string> & vecOut,
                                        const std::string & strToRemove,
                                        bool caseSensitive = c_DEFAULT_CASE_SENSITIVE)
{
    size_t totalRemoved = 0;
    int count = vecOut.size();
    if (count == 0 )
    {
        return 0;
    }

    for (int a1 = count-1;a1 >= 0; --a1)
    {
            if (!StringUtils::contains(vecOut[a1],strToRemove,caseSensitive))
            {
                vecOut.erase(vecOut.begin()+a1);
                ++totalRemoved;
            }
    }
    return totalRemoved;
}


static inline void removeNonAlphaNumericInPlace(std::string & srcStr)
{
    for (int a1=srcStr.size()-1;a1>=0;--a1)
    {
        if (!std::isalnum(srcStr[a1]))
        {
            srcStr.erase(srcStr.begin()+a1);
        }
    }
}

static inline std::string removeNonAlphaNumeric(const std::string & srcStr)
{
    std::string str = srcStr;
    removeNonAlphaNumericInPlace(str);
    return str;
}
}}}} //namespace
#endif //_CBTEK_COMMON_UTILITY_STRING_UTILS_HPP_
