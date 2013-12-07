#ifndef SANGUIS_GUI_WIDGET_OPTIONAL_REF_FWD_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <sanguis/gui/widget/base_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
fcppt::optional<
	sanguis::gui::widget::base &
>
optional_ref;

}
}
}

#endif
