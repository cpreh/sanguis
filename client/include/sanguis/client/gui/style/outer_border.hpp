#ifndef SANGUIS_CLIENT_GUI_STYLE_OUTER_BORDER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_STYLE_OUTER_BORDER_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::gui::style
{

using outer_border = std::integral_constant<sge::rucksack::scalar, 0>;

}

#endif
