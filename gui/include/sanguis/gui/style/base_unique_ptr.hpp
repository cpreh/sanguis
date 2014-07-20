#ifndef SANGUIS_GUI_STYLE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_GUI_STYLE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/gui/style/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace gui
{
namespace style
{

typedef
std::unique_ptr<
	sanguis::gui::style::base
>
base_unique_ptr;

}
}
}

#endif
