/*
 GooeyFiLayoutManager.hpp
 

*/

#pragma once


namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


enum class GooeyFiWidgetLayoutManagerType
{
    Vertical,
    Horizontal,
    Grid
};

class GooeyFiLayoutManager 
{
public:
    //! Virtual Destructor
    virtual ~GooeyFiLayoutManager(){}
};
}}}}//end namespace

