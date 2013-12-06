#ifndef SANGUIS_GUI_WIDGET_REFERENCE_FWD_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_REFERENCE_FWD_HPP_INCLUDED

#include <sanguis/gui/widget/base_fwd.hpp>
#include <fcppt/reference_wrapper_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
fcppt::reference_wrapper<
	sanguis::gui::widget::base
>
reference;

}
}
}

#endif
