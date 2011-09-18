#ifndef SANGUIS_MESSAGES_ADD_CONSOLE_COMMAND_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_CONSOLE_COMMAND_HPP_INCLUDED

#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/string.hpp>
#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			messages::make_message_id<
				types::message::add_console_command
			>::type,
			majutsu::role<
				messages::string,
				roles::command_name
			>,
			majutsu::role<
				messages::string,
				roles::command_description
			>
		>
	>
>::type add_console_command;

}
}

#endif
