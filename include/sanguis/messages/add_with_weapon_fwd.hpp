#ifndef SANGUIS_MESSAGES_ADD_WITH_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WITH_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/add_with_health_fwd.hpp>
#include <sanguis/messages/adapted_types/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
majutsu::composite<
	boost::mpl::vector2<
		sanguis::messages::add_with_health,
		majutsu::role<
			sanguis::messages::adapted_types::optional_primary_weapon_type,
			sanguis::messages::roles::primary_weapon
		>
	>
>
add_with_weapon;

}
}

#endif
