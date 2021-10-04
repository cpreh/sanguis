#ifndef SANGUIS_CLIENT_GUI_STYLE_SPACING_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_STYLE_SPACING_HPP_INCLUDED

#include <sanguis/client/gui/style/inner_border.hpp>
#include <sanguis/client/gui/style/outer_border.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::gui::style
{

using
spacing
=
std::integral_constant<
	sge::rucksack::scalar,
	(
		sanguis::client::gui::style::inner_border::value
		+
		sanguis::client::gui::style::outer_border::value
	)
	*
	2
>;

}

#endif
