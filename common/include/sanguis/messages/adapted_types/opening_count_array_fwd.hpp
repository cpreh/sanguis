#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/size_fwd.hpp>
#include <sanguis/messages/types/opening_count_array_fwd.hpp>
#include <alda/bindings/enum_array_fwd.hpp>

namespace sanguis::messages::adapted_types
{

using opening_count_array = alda::bindings::enum_array<
    sanguis::messages::types::opening_count_array,
    sanguis::messages::adapted_types::size>;

}

#endif
