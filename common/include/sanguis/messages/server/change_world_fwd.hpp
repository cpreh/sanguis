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
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::server
{

using
change_world
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::change_world
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::world_id,
			sanguis::messages::adapted_types::world_id
		>,
		fcppt::record::element<
			sanguis::messages::roles::seed,
			sanguis::messages::adapted_types::seed
		>,
		fcppt::record::element<
			sanguis::messages::roles::generator_name,
			sanguis::messages::adapted_types::string
		>,
		fcppt::record::element<
			sanguis::messages::roles::opening_count,
			sanguis::messages::adapted_types::opening_count_array
		>,
		fcppt::record::element<
			sanguis::messages::roles::world_name,
			sanguis::messages::adapted_types::string
		>,
		fcppt::record::element<
			sanguis::messages::roles::spawn_boss,
			sanguis::messages::adapted_types::bool_
		>
	>
>;

}

#endif
