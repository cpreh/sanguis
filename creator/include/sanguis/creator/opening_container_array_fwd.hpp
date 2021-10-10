#ifndef SANGUIS_CREATOR_OPENING_CONTAINER_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_OPENING_CONTAINER_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_type_fwd.hpp>
#include <fcppt/enum/array_fwd.hpp>

namespace sanguis::creator
{

using opening_container_array =
    fcppt::enum_::array<sanguis::creator::opening_type, sanguis::creator::opening_container>;

}

#endif
