/*
 GooeyFiWidgetImpl.h
 
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

#include "GooeyFiWidget.hpp"
#include <string>

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


class GooeyFiWidgetImpl :public GooeyFiWidget
{
public:
    //! Constructor for GooeyFiWidgetImpl
    /*!
        Detailed description for GooeyFiWidgetImpl
    */
    GooeyFiWidgetImpl();

    /**
    * @brief Setter for m_widgetType
    * @param Value to replace m_widgetType
    */
    void setWidgetType(const GooeyFiWidgetType & value);

    /**
    * @brief Setter for m_label
    * @param Value to replace m_label
    */
    void setLabel(const std::string & value);

    /**
    * @brief Setter for m_id
    * @param Value to replace m_id
    */
    void setId(const std::string & value);


        /**
    * @brief Getter for m_widgetType
    * @return Return copy of m_widgetType
    */
    const GooeyFiWidgetType & getWidgetType() const;

    /**
    * @brief Getter for m_label
    * @return Return copy of m_label
    */
    const std::string & getLabel() const;

    /**
    * @brief Getter for m_id
    * @return Return copy of m_id
    */
    const std::string & getId() const;



    //! Destructor
    ~GooeyFiWidgetImpl();	

private:
        GooeyFiWidgetType m_widgetType;
    std::string m_label;
    std::string m_id;

};
}}}}//end namespace


