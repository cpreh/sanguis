#ifndef SANGUIS_GUI_STYLE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_GUI_STYLE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/gui/style/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace gui
{
namespace style
{

typedef
fcppt::unique_ptr<
	sanguis::gui::style::base
>
base_unique_ptr;

}
}
}

#endif
