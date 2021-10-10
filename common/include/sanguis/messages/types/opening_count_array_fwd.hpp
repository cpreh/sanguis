#ifndef SANGUIS_MESSAGES_TYPES_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/creator/opening_type_fwd.hpp>
#include <sanguis/messages/types/size.hpp>
#include <fcppt/enum/array_fwd.hpp>

namespace sanguis::messages::types
{

using opening_count_array =
    fcppt::enum_::array<sanguis::creator::opening_type, sanguis::messages::types::size>;

}

#endif
