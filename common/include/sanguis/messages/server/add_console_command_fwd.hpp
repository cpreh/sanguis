#ifndef SANGUIS_MESSAGES_SERVER_ADD_CONSOLE_COMMAND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_CONSOLE_COMMAND_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
add_console_command
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::add_console_command
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::command_name,
			sanguis::messages::adapted_types::string
		>,
		fcppt::record::element<
			sanguis::messages::roles::command_description,
			sanguis::messages::adapted_types::string
		>
	>
>;

}
}
}

#endif
