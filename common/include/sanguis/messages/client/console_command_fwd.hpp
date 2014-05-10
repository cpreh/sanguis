#ifndef SANGUIS_MESSAGES_CLIENT_CONSOLE_COMMAND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CONSOLE_COMMAND_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_vector_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id_fwd.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/console_command.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::client::types::make_message_id<
				sanguis::messages::client::types::message::console_command
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string_vector,
				sanguis::messages::roles::console_command
			>
		>
	>
>
console_command;

}
}
}

#endif
