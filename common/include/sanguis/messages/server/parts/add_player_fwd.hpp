#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
metal::join<
	sanguis::messages::server::parts::add_actor,
	metal::list<
		fcppt::record::element<
			sanguis::messages::roles::name,
			sanguis::messages::adapted_types::string
		>
	>
>
add_player;

}
}
}
}

#endif
