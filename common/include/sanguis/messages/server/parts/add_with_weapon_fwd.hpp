#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_status_fwd.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
boost::mpl::vector2<
	majutsu::role<
		sanguis::messages::adapted_types::optional_primary_weapon_type,
		sanguis::messages::roles::primary_weapon
	>,
	majutsu::role<
		sanguis::messages::adapted_types::weapon_status,
		sanguis::messages::roles::weapon_status
	>
>
add_with_weapon;

}
}
}
}

#endif
