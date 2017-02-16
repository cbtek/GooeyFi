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
#include "ColorLoop.h"


namespace cbtek {
namespace common {
namespace utility {

void ColorLoop::generateUniqueColors(const size_t &count)
{
    m_colors.clear();
    for (size_t a1=0;a1<count;++a1)
    {
        Color color = ColorFactory::create(colors::RANDOM);
        if (colorExists(color))
        {
            a1--;
            continue;
        }
        else
        {
            operator <<(color);
        }
    }
}

Color ColorLoop::getNextColor()
{
    if (m_currentColor>=m_colors.size())
    {
        reset();
    }

    Color color=m_colors[m_currentColor];
    ++m_currentColor;
    return color;
}

void ColorLoop::reset()
{
    m_currentColor=0;
}

void ColorLoop::clear()
{
    reset();
    m_colors.clear();
}

Color ColorLoop::getColorAt(size_t ndx) const
{
    return ndx<m_colors.size()?m_colors[ndx]:Color();
}

size_t ColorLoop::getCurrentColorNdx() const
{
    return m_currentColor;
}

void ColorLoop::setCurrentColorNdx(size_t ndx)
{
    m_currentColor=ndx;
}

bool ColorLoop::colorExists(const Color &color)
{
    for (size_t a1 = 0;a1<m_colors.size();++a1)
    {
        if (color==m_colors[a1])
        {
            return true;
        }
    }
    return false;
}

ColorLoop::ColorLoop()
{
}

ColorLoop &ColorLoop::operator <<(const Color &color)
{
    m_colors.push_back(color);
    return *this;
}

ColorLoop &ColorLoop::operator <<(const colors::ColorType &colorType)
{
    m_colors.push_back(ColorFactory::create(colorType));
    return *this;
}

ColorLoop &ColorLoop::operator <<(const colorFunctions::ColorFunction &function)
{
    switch(function)
    {
        case colorFunctions::ADD_5_RANDOM_COLORS:
        for(size_t a1=0;a1<5;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomNamedColor());
        }
        break;
        case colorFunctions::ADD_10_RANDOM_COLORS:
        for(size_t a1=0;a1<10;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomNamedColor());
        }
        break;
        case colorFunctions::ADD_15_RANDOM_COLORS:
        for(size_t a1=0;a1<15;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomNamedColor());
        }
        break;
        case colorFunctions::ADD_20_RANDOM_COLORS:
        for(size_t a1=0;a1<20;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomNamedColor());
        }
        break;
        case colorFunctions::ADD_5_RANDOM_LIGHT_COLORS:
        for(size_t a1=0;a1<5;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomLightColor());
        }
        break;
        case colorFunctions::ADD_10_RANDOM_LIGHT_COLORS:
        for(size_t a1=0;a1<10;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomLightColor());
        }
        break;
        case colorFunctions::ADD_15_RANDOM_LIGHT_COLORS:
        for(size_t a1=0;a1<15;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomLightColor());
        }
        break;
        case colorFunctions::ADD_20_RANDOM_LIGHT_COLORS:
        for(size_t a1=0;a1<20;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomLightColor());
        }
        break;
        case colorFunctions::ADD_5_RANDOM_DARK_COLORS:
        for(size_t a1=0;a1<5;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomDarkColor());
        }
        break;
        case colorFunctions::ADD_10_RANDOM_DARK_COLORS:
        for(size_t a1=0;a1<10;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomDarkColor());
        }
        break;
        case colorFunctions::ADD_15_RANDOM_DARK_COLORS:
        for(size_t a1=0;a1<15;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomDarkColor());
        }
        break;
        case colorFunctions::ADD_20_RANDOM_DARK_COLORS:
        for(size_t a1=0;a1<20;++a1)
        {
            m_colors.push_back(ColorFactory::createRandomDarkColor());
        }
        break;
    default:
        break;
    }


    return *this;
}


}}}//namespace
