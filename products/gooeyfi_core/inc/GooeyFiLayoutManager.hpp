/*
 GooeyFiLayoutManager.hpp
 

*/

#pragma once

#include <memory>
#include <vector>

#include "GooeyFiWidget.hpp"

namespace cbtek {
namespace products {
namespace gooeyfi {
namespace core {


enum class GooeyFiLayoutManagerType
{
    Vertical,
    Horizontal,
    Grid
};


inline static std::string getLayoutTypeString(GooeyFiLayoutManagerType type)
{
    switch(type)
    {
        case GooeyFiLayoutManagerType::Grid: return "GRID";
        case GooeyFiLayoutManagerType::Horizontal: return "HORIZONTAL";
        default: return "VERTICAL";
    }
}

class GooeyFiLayoutManager 
{
public:

    /**
     * @brief GooeyFiWidgetPage::addWidget
     * @param widget
     */
    virtual void addWidget(const GooeyFiWidgetPtr &widget) = 0;


    /**
     * @brief getWidgets
     * @return
     */
    virtual const std::vector<GooeyFiWidgetPtr>& getWidgets() const = 0;

    /**
     * @brief getType
     * @return
     */
    virtual GooeyFiLayoutManagerType getType() const = 0;

    //! Virtual Destructor
    virtual ~GooeyFiLayoutManager(){}
};

typedef std::shared_ptr<GooeyFiLayoutManager>GooeyFiLayoutManagerPtr;
}}}}//end namespace

