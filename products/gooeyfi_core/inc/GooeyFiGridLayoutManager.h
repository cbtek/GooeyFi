/*
 GooeyFiGridLayoutManager.h
 
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
#include <map>

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


class GooeyFiGridLayoutManager :public GooeyFiLayoutManager
{
public:
    //! Constructor for GooeyFiGridLayoutManager
    /*!
        Detailed description for GooeyFiGridLayoutManager
    */
    GooeyFiGridLayoutManager();
        /**
    * @brief Setter for m_widgets
    * @param Value to replace m_widgets
    */
    void setWidgets(const std::map<std::pair<size_t,size_t>, GooeyFiWidgetPtr> & value);


        /**
    * @brief Getter for m_widgets
    * @return Return copy of m_widgets
    */
    const std::map<std::pair<size_t,size_t>, GooeyFiWidgetPtr> & getWidgets() const;



    //! Destructor
    ~GooeyFiGridLayoutManager();	

private:
        std::map<std::pair<size_t,size_t>, GooeyFiWidgetPtr> m_widgets;

};
}}}}//end namespace


