#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_ATTRIBUTE_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_ATTRIBUTE_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/weapon_attribute_fwd.hpp>
#include <sanguis/messages/server/types/weapon_attribute_vector.hpp>
#include <alda/bindings/class_fwd.hpp>
#include <alda/bindings/dynamic_len_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

// TODO: Move this to server::
typedef
alda::bindings::dynamic_len<
	sanguis::messages::server::types::weapon_attribute_vector,
	alda::bindings::class_<
		sanguis::messages::server::types::weapon_attribute
	>
>
weapon_attribute_vector;

}
}
}

#endif
