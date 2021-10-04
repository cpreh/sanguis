#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_IS_PRIMARY_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_IS_PRIMARY_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/adapted_types/bool_fwd.hpp>
#include <alda/bindings/strong_typedef_decl.hpp>


namespace sanguis::messages::adapted_types
{

using
is_primary_weapon
=
alda::bindings::strong_typedef<
	sanguis::is_primary_weapon,
	sanguis::messages::adapted_types::bool_
>;

}

#endif
