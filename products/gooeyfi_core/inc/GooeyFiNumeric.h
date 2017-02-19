/*
 GooeyFiNumeric.h
 
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

enum class GooeyFiNumericType
{
    Float,
    Integer
};

class GooeyFiNumeric :public GooeyFiWidgetImpl
{
public:
    //! Constructor for GooeyFiNumeric
    /*!
        Detailed description for GooeyFiNumeric
    */
    GooeyFiNumeric();

    /**
     * @brief setType
     * @param type
     */
    void setType(GooeyFiNumericType type);

    /**
     * @brief getType
     * @return
     */
    GooeyFiNumericType getType() const;
    /**
    * @brief Setter for m_value
    * @param Value to replace m_value
    */
    void setValue(double value);

    /**
    * @brief Setter for m_increment
    * @param Value to replace m_increment
    */
    void setIncrement(double value);

    /**
    * @brief Setter for m_min
    * @param Value to replace m_min
    */
    void setMin(double value);

    /**
    * @brief Setter for m_max
    * @param Value to replace m_max
    */
    void setMax(double value);


        /**
    * @brief Getter for m_value
    * @return Return copy of m_value
    */
    double getValue() const;

    /**
    * @brief Getter for m_increment
    * @return Return copy of m_increment
    */
    double getIncrement() const;

    /**
    * @brief Getter for m_min
    * @return Return copy of m_min
    */
    double getMin() const;

    /**
    * @brief Getter for m_max
    * @return Return copy of m_max
    */
    double getMax() const;


    /**
     * @brief write
     * @param xml
     */
    void write(cbtek::common::utility::XMLStreamWriter& xml);

    /**
     * @brief getWidgetType
     * @return
     */
    GooeyFiWidgetType getWidgetType() const;

    //! Destructor
    ~GooeyFiNumeric();	

private:

    GooeyFiNumericType m_type;
    double m_value;
    double m_increment;
    double m_min;
    double m_max;

};
}}}}//end namespace


