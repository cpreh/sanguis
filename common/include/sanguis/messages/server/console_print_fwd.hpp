#ifndef SANGUIS_MESSAGES_SERVER_CONSOLE_PRINT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CONSOLE_PRINT_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/console_message.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
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
alda::message::make_class<
	boost::mpl::vector2<
		sanguis::messages::server::types::make_message_id<
			sanguis::messages::server::types::message::console_print
		>,
		majutsu::role<
			sanguis::messages::adapted_types::string,
			sanguis::messages::roles::console_message
		>
	>
>
console_print;

}
}
}

#endif
