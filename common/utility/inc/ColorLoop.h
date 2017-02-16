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
#ifndef _CBTEK_COMMON_UTILITY_COLORLOOP_H
#define _CBTEK_COMMON_UTILITY_COLORLOOP_H

#include "ColorFactory.h"
#include <vector>


namespace cbtek {
namespace common {
namespace utility {

namespace colorFunctions{
enum ColorFunction{
    ADD_5_RANDOM_COLORS,
    ADD_10_RANDOM_COLORS,
    ADD_15_RANDOM_COLORS,
    ADD_20_RANDOM_COLORS,
    ADD_5_RANDOM_LIGHT_COLORS,
    ADD_10_RANDOM_LIGHT_COLORS,
    ADD_15_RANDOM_LIGHT_COLORS,
    ADD_20_RANDOM_LIGHT_COLORS,
    ADD_5_RANDOM_DARK_COLORS,
    ADD_10_RANDOM_DARK_COLORS,
    ADD_15_RANDOM_DARK_COLORS,
    ADD_20_RANDOM_DARK_COLORS
};
}
class ColorLoop
{

public:

    ColorLoop();

    ColorLoop & operator<<(const Color & color);

    ColorLoop & operator<< (const colors::ColorType & colorType);

    ColorLoop & operator<< (const colorFunctions::ColorFunction & function);

    void generateUniqueColors(const size_t & count);

    Color getNextColor();

    void reset();

    void clear();

    Color getColorAt(size_t ndx) const;

    size_t getCurrentColorNdx() const;

    void setCurrentColorNdx(size_t ndx);


private:

    size_t m_currentColor;

    std::vector<Color> m_colors;

    bool colorExists(const Color & color);
};
}}}//namespace
#endif // _CBTEK_COMMON_UTILITY_COLORLOOP_H
