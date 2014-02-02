#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
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
majutsu::composite<
	boost::mpl::vector2<
		sanguis::messages::server::parts::add_actor,
		majutsu::role<
			sanguis::messages::adapted_types::string,
			sanguis::messages::roles::name
		>
	>
>
add_player;

}
}
}
}

#endif
