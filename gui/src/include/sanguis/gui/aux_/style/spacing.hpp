#ifndef SANGUIS_GUI_AUX__STYLE_SPACING_HPP_INCLUDED
#define SANGUIS_GUI_AUX__STYLE_SPACING_HPP_INCLUDED

#include <sanguis/gui/aux_/style/inner_border.hpp>
#include <sanguis/gui/aux_/style/outer_border.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{
namespace style
{

typedef
std::integral_constant<
	sge::rucksack::scalar,
	(
		sanguis::gui::aux_::style::inner_border::value
		+
		sanguis::gui::aux_::style::outer_border::value
	)
	*
	2
>
spacing;

}
}
}
}

#endif
