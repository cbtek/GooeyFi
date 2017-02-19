/*
 GooeyFiWidget.hpp
 
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

#pragma once

#include <memory>

#include "utility/inc/XMLStreamWriter.h"

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {

enum class GooeyFiWidgetType
{
    TextInput,
    PathBrowser,
    Numeric,
    Button
};

inline static std::string getWidgetTypeStr(GooeyFiWidgetType type)
{
    if (type == GooeyFiWidgetType::Button)
    {
        return "BUTTON";
    }
    else if (type == GooeyFiWidgetType::Numeric)
    {
        return "NUMERIC";
    }
    else if (type == GooeyFiWidgetType::PathBrowser)
    {
        return "PATHBROWSER";
    }
    else return "TEXTINPUT";
}

class GooeyFiWidget 
{
public:

    /**
     * @brief getWidgetType
     * @return
     */
    virtual GooeyFiWidgetType getWidgetType() const = 0;

    /**
     * @brief write
     * @param xml
     */
    virtual void write(cbtek::common::utility::XMLStreamWriter& xml) = 0;

    //! Virtual Destructor
    virtual ~GooeyFiWidget(){}
};
typedef std::shared_ptr<GooeyFiWidget> GooeyFiWidgetPtr;
}}}}//end namespace

