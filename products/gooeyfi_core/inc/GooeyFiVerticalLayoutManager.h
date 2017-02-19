/*
 GooeyFiVerticalLayoutManager.h
 
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

#include "GooeyFiLayoutManager.hpp"

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


class GooeyFiVerticalLayoutManager :public GooeyFiLayoutManager
{
public:
    //! Constructor for GooeyFiVerticalLayoutManager
    /*!
        Detailed description for GooeyFiVerticalLayoutManager
    */
    GooeyFiVerticalLayoutManager();
        /**
    * @brief Setter for m_widgets
    * @param Value to replace m_widgets
    */
    void setWidgets(const std::vector<GooeyFiWidgetPtr> & value);


    /**
     * @brief addWidget
     * @param widget
     */
    void addWidget(const GooeyFiWidgetPtr& widget);


        /**
    * @brief Getter for m_widgets
    * @return Return copy of m_widgets
    */
     const std::vector<GooeyFiWidgetPtr>& getWidgets() const;


    /**
     * @brief getType
     * @return
     */
    GooeyFiLayoutManagerType getType() const;


    //! Destructor
    ~GooeyFiVerticalLayoutManager();	

private:
        std::vector<GooeyFiWidgetPtr> m_widgets;

};
}}}}//end namespace


