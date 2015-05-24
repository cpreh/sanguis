#ifndef SANGUIS_GUI_WIDGET_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/gui/widget/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
fcppt::unique_ptr<
	sanguis::gui::widget::base
>
base_unique_ptr;

}
}
}

#endif
