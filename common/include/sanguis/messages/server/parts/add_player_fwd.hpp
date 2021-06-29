#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

using
add_player
=
fcppt::mpl::list::append<
	sanguis::messages::server::parts::add_actor,
	fcppt::mpl::list::object<
		fcppt::record::element<
			sanguis::messages::roles::name,
			sanguis::messages::adapted_types::string
		>
	>
>;

}
}
}
}

#endif
