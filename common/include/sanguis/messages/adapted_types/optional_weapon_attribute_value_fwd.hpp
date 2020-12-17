#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_OPTIONAL_WEAPON_ATTRIBUTE_VALUE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_OPTIONAL_WEAPON_ATTRIBUTE_VALUE_FWD_HPP_INCLUDED

#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_value_fwd.hpp>
#include <alda/bindings/optional_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

using
optional_weapon_attribute_value
=
alda::bindings::optional<
	sanguis::weapon_attribute_value,
	sanguis::messages::adapted_types::weapon_attribute_value
>;

}
}
}

#endif
