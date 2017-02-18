/*
 GooeyFiButton.h
 
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


enum class GooeyFiButtonType
{
    Radio,
    Checkbox,
    Action
};

class GooeyFiButton :public GooeyFiWidgetImpl
{
public:
    //! Constructor for GooeyFiButton
    /*!
        Detailed description for GooeyFiButton
    */
    GooeyFiButton();
        /**
    * @brief Setter for m_buttonType
    * @param Value to replace m_buttonType
    */
    void setButtonType(const GooeyFiButtonType & value);


        /**
    * @brief Getter for m_buttonType
    * @return Return copy of m_buttonType
    */
    const GooeyFiButtonType & getButtonType() const;



    //! Destructor
    ~GooeyFiButton();	

private:
        GooeyFiButtonType m_buttonType;

};
}}}}//end namespace


