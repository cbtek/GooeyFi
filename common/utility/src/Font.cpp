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
#include "Font.h"
#include "utility/inc/StringUtils.hpp"

using namespace cbtek::common::utility;

namespace cbtek {
namespace common {
namespace utility {

Font::Font()
{
    m_changed=false;
    m_fontFamily="times";
    m_pointSize=10;
    m_isBold=false;
    m_isItalic=false;
    m_isUnderlined=false;
}

Font::Font(const std::string &fontFamily, const size_t &pointSize, const bool &isBold, const bool &isItalic, const bool &isUnderlined)
{
    m_fontFamily=fontFamily;
    m_pointSize=pointSize;
    m_isBold=isBold;
    m_isItalic=isItalic;
    m_isUnderlined=isUnderlined;
    m_changed=true;
}

bool Font::operator ==(const Font &font)
{
    return (font.getFontFamily()==m_fontFamily &&
            font.getPointSize()==m_pointSize &&
            font.isBold()==m_isBold &&
            font.isItalic()==m_isItalic &&
            font.isUnderlined()==m_isUnderlined);
}

void Font::setFontFamily(const std::string &fontFamily)
{
    m_fontFamily=fontFamily;
    m_changed=true;
}

void Font::setPointSize(const size_t &pointSize)
{
    m_pointSize=pointSize;
    m_changed=true;
}

void Font::setBold(const bool &enabled)
{
    m_isBold=enabled;
    m_changed=true;
}

void Font::setItalic(const bool &enabled)
{
    m_isItalic=enabled;
    m_changed=true;
}

void Font::setUnderlined(const bool &enabled)
{
    m_isUnderlined=enabled;
    m_changed=true;
}

bool Font::isBold() const
{
    return m_isBold;
}

bool Font::isItalic() const
{
    return m_isItalic;
}

bool Font::isUnderlined() const
{
    return m_isUnderlined;
}

std::string Font::getFontFamily() const
{
    return m_fontFamily;
}

size_t Font::getPointSize() const
{
    return m_pointSize;
}

std::string Font::toString() const
{
    return m_fontFamily +","+StringUtils::toString(m_pointSize) + "," + StringUtils::toString(m_isBold)+ "," + StringUtils::toString(m_isItalic)+ "," + StringUtils::toString(m_isUnderlined);
}

bool Font::hasDefaultChanged() const
{
    return m_changed;
}

void Font::setChanged(bool flag)
{
    m_changed=flag;
}

void Font::setFontColor(const Color &c)
{
    m_color=c;
}

Color Font::getFontColor() const
{
    return m_color;
}




}}}//namespace
