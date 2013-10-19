#ifndef SANGUIS_MESSAGES_ADD_OWN_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_OWN_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/add_player_basic_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/adapted_types/string_vector_fwd.hpp>
#include <sanguis/messages/roles/weapon_description.hpp>
#include <sanguis/messages/types/message.hpp>
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
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::add_player_basic<
				sanguis::messages::types::message::add_own_player
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string_vector,
				sanguis::messages::roles::weapon_description
			>
		>
	>
>
add_own_player;

}
}

#endif
