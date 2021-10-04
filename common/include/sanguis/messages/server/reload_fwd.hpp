#ifndef SANGUIS_MESSAGES_SERVER_RELOAD_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_RELOAD_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/duration_fwd.hpp>
#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::server
{

using
reload
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::reload
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::is_primary_weapon,
			sanguis::messages::adapted_types::is_primary_weapon
		>,
		fcppt::record::element<
			sanguis::messages::roles::reload_time,
			sanguis::messages::adapted_types::duration
		>
	>
>;

}

#endif
