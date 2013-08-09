#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_TYPE_FWD_HPP_INCLUDED

#include <sanguis/weapon_types_fwd.hpp>
#include <sanguis/messages/adapted_types/primary_weapon_type_fwd.hpp>
#include <sanguis/messages/adapted_types/secondary_weapon_type_fwd.hpp>
#include <alda/bindings/variant_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::variant<
	sanguis::weapon_types,
	boost::mpl::vector2<
		sanguis::messages::adapted_types::primary_weapon_type,
		sanguis::messages::adapted_types::secondary_weapon_type
	>
>
weapon_type;

}
}
}

#endif
