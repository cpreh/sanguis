#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_TYPE_FWD_HPP_INCLUDED

#include <sanguis/weapon_types_fwd.hpp>
#include <sanguis/messages/adapted_types/primary_weapon_type_fwd.hpp>
#include <sanguis/messages/adapted_types/secondary_weapon_type_fwd.hpp>
#include <alda/bindings/variant_decl.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sanguis::messages::adapted_types
{

using
weapon_type
=
alda::bindings::variant<
	sanguis::weapon_types,
	fcppt::mpl::list::object<
		sanguis::messages::adapted_types::primary_weapon_type,
		sanguis::messages::adapted_types::secondary_weapon_type
	>
>;

}

#endif
