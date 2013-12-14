#ifndef SANGUIS_GUI_WIDGET_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/gui/widget/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
std::unique_ptr<
	sanguis::gui::widget::base
>
unique_ptr;

}
}
}

#endif
