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
#ifndef _CBTEK_COMMON_UTILITY_FONT_H
#define _CBTEK_COMMON_UTILITY_FONT_H

#include <string>

#include "utility/inc/Color.h"

namespace cbtek {
namespace common {
namespace utility {

namespace textAlignment
{
    enum Alignment
    {
        LEFT,
        MIDDLE,
        RIGHT
    };

    enum HorizontalAlignment
       {
           ALIGN_HGENERAL,
           ALIGN_LEFT,
           ALIGN_HCENTER,
           ALIGN_RIGHT,
           ALIGN_HFILL,
           ALIGN_HJUSTIFY,
           ALIGN_HMERGE,
           ALIGN_HDISTRIBUTED
       };

       enum VerticalAlignment
       {
           ALIGN_TOP,
           ALIGN_VCENTER,
           ALIGN_BOTTOM,
           ALIGN_VJUSTIFY,
           ALIGN_VDISTRIBUTED
       };
}
class Font
{
public:

    Font();

    Font(const std::string & fontFamily, const size_t & pointSize=10, const bool & isBold=false, const bool & isItalic = false, const bool & isUnderlined=false);

    bool operator==(const Font & font);

    void setFontFamily(const std::string & fontFamily);

    void setPointSize(const size_t & pointSize);

    void setBold(const bool & enabled);

    void setItalic(const bool & enabled);

    void setUnderlined(const bool & enabled);

    bool isBold() const;

    bool isItalic() const;

    bool isUnderlined() const;

    std::string getFontFamily() const;

    size_t getPointSize()const;

    std::string toString() const;

    bool hasDefaultChanged() const;

    void setChanged(bool flag);

    void setFontColor(const Color &c);

    Color getFontColor() const;

private:

    bool m_changed;

    bool m_isUnderlined;

    bool m_isBold;

    bool m_isItalic;

    size_t m_pointSize;

    std::string m_fontFamily;

    Color m_color;

};

}}}//namespace

#endif // _CBTEK_COMMON_UTILITY_FONT_H
