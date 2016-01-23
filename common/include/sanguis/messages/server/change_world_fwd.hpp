#ifndef SANGUIS_MESSAGES_SERVER_CHANGE_WORLD_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CHANGE_WORLD_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/bool_fwd.hpp>
#include <sanguis/messages/adapted_types/opening_count_array_fwd.hpp>
#include <sanguis/messages/adapted_types/seed_fwd.hpp>
#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/adapted_types/world_id_fwd.hpp>
#include <sanguis/messages/roles/generator_name.hpp>
#include <sanguis/messages/roles/opening_count.hpp>
#include <sanguis/messages/roles/seed.hpp>
#include <sanguis/messages/roles/spawn_boss.hpp>
#include <sanguis/messages/roles/world_id.hpp>
#include <sanguis/messages/roles/world_name.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
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

typedef
alda::message::record<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::change_world
	>,
	boost::mpl::vector6<
		majutsu::role<
			sanguis::messages::adapted_types::world_id,
			sanguis::messages::roles::world_id
		>,
		majutsu::role<
			sanguis::messages::adapted_types::seed,
			sanguis::messages::roles::seed
		>,
		majutsu::role<
			sanguis::messages::adapted_types::string,
			sanguis::messages::roles::generator_name
		>,
		majutsu::role<
			sanguis::messages::adapted_types::opening_count_array,
			sanguis::messages::roles::opening_count
		>,
		majutsu::role<
			sanguis::messages::adapted_types::string,
			sanguis::messages::roles::world_name
		>,
		majutsu::role<
			sanguis::messages::adapted_types::bool_,
			sanguis::messages::roles::spawn_boss
		>
	>
>
change_world;

}
}
}

#endif
