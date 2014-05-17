#ifndef SANGUIS_GUI_NEEDED_WIDTH_FROM_STRINGS_HPP_INCLUDED
#define SANGUIS_GUI_NEEDED_WIDTH_FROM_STRINGS_HPP_INCLUDED

#include <sanguis/gui/needed_width.hpp>
#include <sanguis/gui/string_container.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sge/font/object_fwd.hpp>


namespace sanguis
{
namespace gui
{

SANGUIS_GUI_SYMBOL
sanguis::gui::needed_width const
needed_width_from_strings(
	sge::font::object &,
	sanguis::gui::string_container const &
);

}
}

#endif
