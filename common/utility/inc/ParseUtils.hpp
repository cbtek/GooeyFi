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


#ifndef _CBTEK_COMMON_UTILITY_PARSEUTILS_H_
#define _CBTEK_COMMON_UTILITY_PARSEUTILS_H_

#include <istream>
#include <string>
#include <cstring>

namespace cbtek {
namespace common {
namespace utility {
namespace ParseUtils {

const static bool c_DEFAULT_REVERSE_BYTES = false;

///
/// @brief Reverses all bytes in a plain old data type
/// @param src The plain old data type to reverse
/// @return The reversed plain old data type
///
template <typename T>
inline T reverse(T  src)
{
    T dest;
    char * fb = (char *)(&src);
    char * tb = (char *)(&dest);
    size_t count = sizeof(T);
    for (size_t i = 0; i < count; ++i)
    {
        tb[i]=fb[(count-1)-i];
    }
    return dest;
}

/**
* @brief Templated function to read
*        plain old data types from an input stream
* @param[out] in Reference to input stream
* @param reverseBytes Should bytes be reversed before
* returning the value?
* @return Return the requested POD type from input stream
*/
template <typename T>
inline T read(std::istream & in,
              bool reverseBytes = c_DEFAULT_REVERSE_BYTES)
{
    size_t size = sizeof(T);
    if (size==1)return (T)in.get();
    char * buffer = new char[size];
    T value;
    in.read(buffer,size);
    memcpy(&value,buffer,size);

    delete [] buffer;
    if (reverseBytes)
    {
        return reverse<T>(value);
    }
    else return value;
}

/**
 * @brief Read value POD type (T) from the data buffer
 * @param data The data buffer to read from
 * @param reverseBytes Should I reverse bytes in
 * the return value?
 * @return Return the requested POD type from data buffer
 */
template <typename T>
inline T read(const char * data,
              size_t & offset,
              bool reverseBytes = c_DEFAULT_REVERSE_BYTES)
{
    T value;
    size_t byteSize=sizeof(value);
    memcpy(&value,&data[offset],byteSize);
    offset+=byteSize;
    if (reverseBytes)
    {
        return reverse<T>(value);
    }
    else return value;
}

/**
 * @brief Write value type (T) to output stream (out)
 * @param[out] out The output stream to write to
 * @param value The value to be written
 * @return Return true upon success, false if stream
 * is invalid.
 */
template <typename T>
inline bool write(std::ostream & out,
                  const T & value)
{
    if (!out)return false;
    const char * buffer = reinterpret_cast<const char *>(&value);
    out.write(buffer,sizeof(T));
    return true;
}

/**
* @brief Reads a string from the input stream
* @param[out] in Reference to input stream
* @param[out] stringOut Reference to string out variable
* @param count Number of bytes to read from input stream
* @return true if read was successful otherwise false
*/
inline bool readString(std::istream & in,
                std::string & stringOut,
                size_t count)
{

    for (size_t a1 = 0;a1<(size_t)count;++a1)
    {
        stringOut.push_back(static_cast<char>(in.get()));
    }
    return true;
}

/**
* @brief Read std::string from byte buffer
* @param data The buffer to read from
* @param[out] offset  The offset into data
* @param stringOut The output string
* @param count Number of bytes to read
* @return true if successful, false otherwise
*/
inline bool readString(const char * data,
                size_t & offset,
                std::string & stringOut,
                size_t count)
{
    for (size_t a1 = 0;a1<(size_t)count;++a1)
    {
        stringOut.push_back(data[offset+a1]);
    }
    offset+=count;
    return true;
}

/**
* @brief Read bytes from input stream
* @param[out] in Reference to input stream
* @param[out] bytesOut Pointer to array of characters
* @param count Number of bytes to read from input stream
* @return true if read was successful otherwise false
*/
inline bool readBytes(std::istream & in,
               char ** bytesOut,
               size_t count)
{
    *bytesOut = new char[count];
    in.read(*bytesOut,count);
    return true;
}

/**
* @brief Read bytes from input stream
* @param[out] in The input stream
* @param[out] bytesOut The buffer to read into
* @param count The number of bytes to read from in
* @param offset The offset into in
* @return true if successful, false if stream
* is invalid
*/
inline bool readBytesAt(std::istream &in,
                 char **bytesOut,
                 size_t count,
                 size_t offset)
{
    in.seekg(offset,std::ios::beg);
    if (!in)return false;
    *bytesOut = new char[count];
    in.read(*bytesOut,count);
    return true;
}
}}}}//end namespace

#endif //_CBTEK_COMMON_UTILITY_PARSEUTILS_H_

