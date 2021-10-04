#ifndef SANGUIS_MESSAGES_CLIENT_INFO_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_INFO_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/player_name.hpp>
#include <alda/bindings/record_variadic_decl.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::client
{

using
info
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::info
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::player_name,
			sanguis::messages::adapted_types::string
		>
	>
>;

}

#endif
