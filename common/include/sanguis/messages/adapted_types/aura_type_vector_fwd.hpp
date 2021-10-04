#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_AURA_TYPE_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_AURA_TYPE_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/messages/adapted_types/aura_type_fwd.hpp>
#include <sanguis/messages/adapted_types/dynamic_len_fwd.hpp>


namespace sanguis::messages::adapted_types
{

using
aura_type_vector
=
sanguis::messages::adapted_types::dynamic_len<
	sanguis::aura_type_vector,
	sanguis::messages::adapted_types::aura_type
>;

}

#endif
