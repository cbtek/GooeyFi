/*
 GooeyFiPathBrowser.h
 
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


enum class GooeyFiPathBrowserType
{
    File,
    Folder
};


class GooeyFiPathBrowser :public GooeyFiWidgetImpl
{
public:
    //! Constructor for GooeyFiPathBrowser
    /*!
        Detailed description for GooeyFiPathBrowser
    */
    GooeyFiPathBrowser();
        /**
    * @brief Setter for m_buttonType
    * @param Value to replace m_buttonType
    */
    void setButtonType(const GooeyFiPathBrowserType & value);

    /**
    * @brief Setter for m_pathValue
    * @param Value to replace m_pathValue
    */
    void setPathValue(const std::string & value);

    /**
    * @brief Setter for m_browseButtonLabel
    * @param Value to replace m_browseButtonLabel
    */
    void setBrowseButtonLabel(const std::string & value);


        /**
    * @brief Getter for m_buttonType
    * @return Return copy of m_buttonType
    */
    const GooeyFiPathBrowserType & getButtonType() const;

    /**
    * @brief Getter for m_pathValue
    * @return Return copy of m_pathValue
    */
    const std::string & getPathValue() const;

    /**
    * @brief Getter for m_browseButtonLabel
    * @return Return copy of m_browseButtonLabel
    */
    const std::string & getBrowseButtonLabel() const;



    //! Destructor
    ~GooeyFiPathBrowser();	

private:
        GooeyFiPathBrowserType m_buttonType;
    std::string m_pathValue;
    std::string m_browseButtonLabel;

};
}}}}//end namespace


