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
#include "Color.h"
#include <sstream>
#include "ColorFactory.h"

using namespace cbtek::common::utility;

namespace cbtek {
namespace common {
namespace utility {

inline static std::string toHex(int value)
{
    std::ostringstream stream;
    stream <<std::hex<< value;
    return stream.str();
}

Color::Color()
{
    m_red=0;
    m_blue=0;
    m_green=0;
    m_alpha=255;
}

Color::Color(std::uint32_t color)
{
    m_blue = color & 0xFF; color >>= 8;
    m_green = color & 0xFF; color >>= 8;
    m_red = color & 0xFF; color >>= 8;
    m_alpha = color & 0xFF; /* color >>= 8; */
}

Color::Color(const std::string &rgbaHex)
{
    (*this)=ColorFactory::create(rgbaHex);
}

Color::Color(const std::string &name, const uint8_t &red, const uint8_t &green, const uint8_t &blue, const uint8_t &alpha)
{
    m_name=name;
    m_red=red;
    m_blue=blue;
    m_green=green;
    m_alpha=alpha;
}

void Color::setName(const std::string & name)
{
    m_name=name;
}

std::string Color::getName() const
{
    return m_name;
}
Color::Color(const uint8_t &red, const uint8_t &green, const uint8_t &blue, const uint8_t &alpha)
{
    m_red=red;
    m_blue=blue;
    m_green=green;
    m_alpha=alpha;
}

void Color::set(const uint8_t &red, const uint8_t &green, const uint8_t &blue, const uint8_t &alpha)
{
    m_red=red;
    m_blue=blue;
    m_green=green;
    m_alpha=alpha;
}

uint8_t Color::getAlpha() const
{
    return m_alpha;
}

std::uint32_t Color::toInteger() const
{
  return (((((m_alpha << 8) + m_red) << 8) + m_green) << 8) + m_blue;
}

std::string Color::toString(const colorStringStyle::ColorStringStyle &style) const
{
    std::ostringstream out;
    switch (style)
    {
        case colorStringStyle::RGBA_255:
        out << (int)m_red<<" "<<(int)m_green<<" "<<(int)m_blue<<" "<<(int)m_alpha;
        return out.str();
        break;

        case colorStringStyle::RGB_255:
        out << (int)m_red<<" "<<(int)m_green<<" "<<(int)m_blue;
        return out.str();
        break;

        case colorStringStyle::RGBA_FLOAT:
        out << (float)m_red*0.003921568f<<" "<<(float)m_green*0.003921568f<<" "<<(float)m_blue*0.003921568f<<" "<<(float)m_alpha*0.003921568f;
        return out.str();
        break;

        case colorStringStyle::RGB_FLOAT:
        out << (float)m_red*0.003921568f<<" "<<(float)m_green*0.003921568f<<" "<<(float)m_blue*0.003921568f;
        return out.str();
        break;

        case colorStringStyle::RGBA_HTML_HEX:

        out<<"#"<<
             (m_red<16?"0":"")<<toHex(m_red)<<
             (m_green<16?"0":"")<<toHex(m_green)<<
             (m_blue<16?"0":"")<<toHex(m_blue)<<
             (m_alpha<16?"0":"")<<toHex(m_alpha);

        return out.str();
        break;
        case colorStringStyle::ARGB_HTML_HEX:

        out<<"#"<<
             (m_alpha<16?"0":"")<<toHex(m_alpha)<<
             (m_red<16?"0":"")<<toHex(m_red)<<
             (m_green<16?"0":"")<<toHex(m_green)<<
             (m_blue<16?"0":"")<<toHex(m_blue);

        return out.str();
        break;

        case colorStringStyle::RGB_HTML_HEX:
        out<<"#"<<
             (m_red<16?"0":"")<<toHex(m_red)<<
             (m_green<16?"0":"")<<toHex(m_green)<<
             (m_blue<16?"0":"")<<toHex(m_blue);

        return out.str();
        break;

    default:
        break;
    }
    return out.str();
}

bool Color::isTransparent() const
{
    return (m_alpha==0);
}


uint8_t Color::getBlue() const
{
    return m_blue;
}

uint8_t Color::getGreen() const
{
    return m_green;
}

uint8_t Color::getRed() const
{
    return m_red;
}

bool Color::operator ==(const Color &color) const
{
    return (m_red==color.getRed() && m_blue==color.getBlue() && m_green==color.getGreen());
}

bool Color::operator !=(const Color &color) const
{
    return (m_red!=color.getRed() || m_blue!=color.getBlue() || m_green!=color.getGreen());
}

void Color::setRed(const uint8_t &red)
{
    m_red=red;
}

void Color::setAlpha(const uint8_t &alpha)
{
    m_alpha=alpha;
}

void Color::setBlue(const uint8_t &blue)
{
    m_blue=blue;
}

void Color::setGreen(const uint8_t &green)
{
    m_green=green;
}

}}}//namespace
