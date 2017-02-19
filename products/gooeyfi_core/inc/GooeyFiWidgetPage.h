/*
 GooeyFiWidgetPage.h
 
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
#include "GooeyFiLayoutManager.hpp"

#include <vector>

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


class GooeyFiWidgetPage 
{
public:
    //! Constructor for GooeyFiWidgetPage
    /*!
        Detailed description for GooeyFiWidgetPage
    */
    GooeyFiWidgetPage();
        /**
    * @brief Setter for m_title
    * @param Value to replace m_title
    */
    void setTitle(const std::string & value);


        /**
    * @brief Getter for m_title
    * @return Return copy of m_title
    */
    const std::string & getTitle() const;


    /**
     * @brief addWidget
     * @param widget
     */
    void addWidget(const GooeyFiWidgetPtr& widget);

    /**
     * @brief setLayout
     * @param layout
     */
    void setLayout(const GooeyFiLayoutManagerPtr& layout);

    /**
     * @brief getLayout
     * @return
     */
    const GooeyFiLayoutManager * getLayout() const;

    //! Destructor
    ~GooeyFiWidgetPage();	

private:
        std::vector<GooeyFiWidgetPtr> m_widgets;
        std::string m_title;
        GooeyFiLayoutManagerPtr m_layout;
};
}}}}//end namespace


