#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__MAX_EXPONENT_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__MAX_EXPONENT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

typedef
std::integral_constant<
	sge::image::size_type,
	10u
>
max_exponent;

}
}
}
}

#endif
