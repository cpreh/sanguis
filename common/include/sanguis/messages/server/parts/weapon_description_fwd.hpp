#ifndef SANGUIS_MESSAGES_SERVER_PARTS_WEAPON_DESCRIPTION_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_WEAPON_DESCRIPTION_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/duration_fwd.hpp>
#include <sanguis/messages/adapted_types/magazine_size_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_vector_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_type_fwd.hpp>
#include <sanguis/messages/roles/magazine_base_size.hpp>
#include <sanguis/messages/roles/magazine_extra_size.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
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
boost::mpl::vector6<
	majutsu::role<
		sanguis::messages::adapted_types::weapon_type,
		sanguis::messages::roles::weapon_type
	>,
	majutsu::role<
		sanguis::messages::adapted_types::magazine_size,
		sanguis::messages::roles::magazine_base_size
	>,
	majutsu::role<
		sanguis::messages::adapted_types::magazine_size,
		sanguis::messages::roles::magazine_extra_size
	>,
	majutsu::role<
		sanguis::messages::adapted_types::magazine_size,
		sanguis::messages::roles::magazine_remaining
	>,
	majutsu::role<
		sanguis::messages::adapted_types::duration,
		sanguis::messages::roles::reload_time
	>,
	majutsu::role<
		sanguis::messages::adapted_types::weapon_attribute_vector,
		sanguis::messages::roles::weapon_attribute_container
	>
>
weapon_description;

}
}
}
}

#endif
