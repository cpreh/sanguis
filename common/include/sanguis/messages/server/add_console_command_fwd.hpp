#ifndef SANGUIS_MESSAGES_SERVER_ADD_CONSOLE_COMMAND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_CONSOLE_COMMAND_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
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
		sanguis::messages::server::types::message::add_console_command
	>,
	boost::mpl::vector2<
		majutsu::role<
			sanguis::messages::adapted_types::string,
			sanguis::messages::roles::command_name
		>,
		majutsu::role<
			sanguis::messages::adapted_types::string,
			sanguis::messages::roles::command_description
		>
	>
>
add_console_command;

}
}
}

#endif
