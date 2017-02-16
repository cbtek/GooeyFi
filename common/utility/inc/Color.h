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
#ifndef _CBTEK_COMMON_UTILITY_COLOR_H
#define _CBTEK_COMMON_UTILITY_COLOR_H

#include <cstdint>
#include <string>
#include <memory>

namespace cbtek {
namespace common {
namespace utility {

namespace colorStringStyle
{
    enum ColorStringStyle
    {
        RGB_255        //eg. 255 127 64
        ,RGBA_255      //eg. 255 127 64 255
        ,RGB_FLOAT     //eg. 1.0 0.5 0.25
        ,RGBA_FLOAT    //eg. 1.0 0.5 0.25 1.0
        ,RGB_HTML_HEX  //eg. #FFAA33
        ,RGBA_HTML_HEX //eg. #FFAA33AA
        ,ARGB_HTML_HEX //eg. #AARRGGBB
    };
}
class Color
{
public:

    Color();

    Color(std::uint32_t color);

    Color(const std::string & rgbaHex);

    Color(const std::string & name,const uint8_t & red,
          const uint8_t & green,
          const uint8_t & blue,
          const uint8_t & alpha=255);

    Color(const uint8_t & red,
          const uint8_t & green,
          const uint8_t & blue,
          const uint8_t & alpha=255);


    void set (const uint8_t & red,
              const uint8_t & green,
              const uint8_t & blue,
              const uint8_t & alpha=255);

    void setRed(const uint8_t & red);

    void setGreen(const uint8_t & green);

    void setBlue(const uint8_t & blue);

    void setAlpha(const uint8_t & alpha);

    uint8_t getRed() const;

    std::uint32_t toInteger() const;

    bool operator==(const Color & color) const;

    bool operator!=(const Color & color) const;

    uint8_t getGreen() const;

    uint8_t getBlue() const;

    uint8_t getAlpha() const;

    std::string toString(const colorStringStyle::ColorStringStyle &style=colorStringStyle::RGBA_255) const;

    bool isTransparent() const;

    std::string getName() const;

    void setName(const std::string & name);
private:

    uint8_t m_red;

    uint8_t m_green;

    uint8_t m_blue;

    uint8_t m_alpha;

    std::string m_name;

};
typedef std::shared_ptr<Color> ColorPtr;
}}}//namespace
#endif // _CBTEK_COMMON_UTILITY_COLOR_H
