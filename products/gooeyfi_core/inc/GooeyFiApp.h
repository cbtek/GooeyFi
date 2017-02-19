/*
 GooeyFiApp.h
 
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

#include "GooeyFiWidgetPage.h"

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {

class GooeyFiApp
{
public:
    //! Constructor for GooeyFiApp
    /*!
        Detailed description for GooeyFiApp
    */
    GooeyFiApp(const std::string& filePath);
    
    /**
     * @brief addPage
     * @param page
     */
    void addPage(const GooeyFiWidgetPage& page);

    /**
     * @brief getPage
     * @param index
     * @return
     */
    const GooeyFiWidgetPage& getPage(size_t index) const;

    /**
     * @brief getPageCount
     * @return
     */
    size_t getPageCount() const;

    /**
     * @brief getPages
     * @return
     */
    const std::vector<GooeyFiWidgetPage> &getPages() const;

    /**
     * @brief setPages
     * @param pages
     */
    void setPages(const std::vector<GooeyFiWidgetPage>& pages);

    /**
     * @brief read
     */
    void read();

    /**
     * @brief write
     */
    void write();

    //! Destructor
    ~GooeyFiApp();

private:
    std::string m_currentFilePath;
    std::string m_title;
    std::vector<GooeyFiWidgetPage> m_pages;
};
}}}}//end namespace


