#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_MAX_EXPONENT_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_MAX_EXPONENT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tools::libmergeimage::impl
{

using max_exponent = std::integral_constant<
    sge::image::size_type,
    10U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    >;

}

#endif
