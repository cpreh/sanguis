#ifndef SANGUIS_MESSAGES_CLIENT_CONSOLE_COMMAND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CONSOLE_COMMAND_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_vector_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/console_command.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::client
{

using
console_command
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::console_command
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::console_command,
			sanguis::messages::adapted_types::string_vector
		>
	>
>;

}

#endif
