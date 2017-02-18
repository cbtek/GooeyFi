/*
    GooeyFiWidgetImpl.cpp
    
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
//----------------------------------------
//GooeyFiWidgetImpl.cpp generated by CBTek Solutions on 02-17-2017 at 06:11:23 PM
//----------------------------------------
#include "GooeyFiWidgetImpl.h"

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


GooeyFiWidgetImpl::GooeyFiWidgetImpl()
{

}

GooeyFiWidgetImpl::~GooeyFiWidgetImpl()
{

}

void GooeyFiWidgetImpl::setWidgetType(const GooeyFiWidgetType & value)
{
    m_widgetType=value;
}

void GooeyFiWidgetImpl::setLabel(const std::string & value)
{
    m_label=value;
}

void GooeyFiWidgetImpl::setId(const std::string & value)
{
    m_id=value;
}



const GooeyFiWidgetType &GooeyFiWidgetImpl::getWidgetType() const
{
    return m_widgetType;
}

const std::string &GooeyFiWidgetImpl::getLabel() const
{
    return m_label;
}

const std::string &GooeyFiWidgetImpl::getId() const
{
    return m_id;
}


}}}}//end namespace


