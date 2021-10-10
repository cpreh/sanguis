#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_BUFF_TYPE_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_BUFF_TYPE_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <sanguis/messages/adapted_types/buff_type_fwd.hpp>
#include <sanguis/messages/adapted_types/dynamic_len_fwd.hpp>

namespace sanguis::messages::adapted_types
{

using buff_type_vector = sanguis::messages::adapted_types::
    dynamic_len<sanguis::buff_type_vector, sanguis::messages::adapted_types::buff_type>;

}

#endif
