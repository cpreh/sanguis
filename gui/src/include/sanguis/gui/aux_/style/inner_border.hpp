#ifndef SANGUIS_GUI_AUX__STYLE_INNER_BORDER_HPP_INCLUDED
#define SANGUIS_GUI_AUX__STYLE_INNER_BORDER_HPP_INCLUDED

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
	2
>
inner_border;

}
}
}
}

#endif
