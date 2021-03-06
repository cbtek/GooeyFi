/*
 GooeyFiTextInput.h
 
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

#include "GooeyFiWidgetImpl.h"
#include <string>

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {

enum class GooeyFiTextInputType
{
    SingleLine,
    MultiLine,
    Password
};


class GooeyFiTextInput :public GooeyFiWidgetImpl
{
public:
    //! Constructor for GooeyFiTextInput
    /*!
        Detailed description for GooeyFiTextInput
    */
    GooeyFiTextInput();
        /**
    * @brief Setter for m_text
    * @param Value to replace m_text
    */
    void setText(const std::string & value);


        /**
    * @brief Getter for m_text
    * @return Return copy of m_text
    */
    const std::string & getText() const;

    /**
     * @brief write
     * @param xml
     */
    void write(cbtek::common::utility::XMLStreamWriter& xml);

    /**
     * @brief setType
     * @param type
     */
    void setType(GooeyFiTextInputType type);

    /**
     * @brief getType
     * @return
     */
    GooeyFiTextInputType getType() const;

    /**
     * @brief getWidgetType
     * @return
     */
    GooeyFiWidgetType getWidgetType() const;

    //! Destructor
    ~GooeyFiTextInput();	

private:
        std::string m_text;
        GooeyFiTextInputType m_type;

};
}}}}//end namespace


