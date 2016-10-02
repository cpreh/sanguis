#ifndef SANGUIS_MESSAGES_SERVER_CONSOLE_PRINT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CONSOLE_PRINT_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/console_message.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
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
		sanguis::messages::server::types::message::console_print
	>,
	boost::mpl::vector1<
		fcppt::record::element<
			sanguis::messages::roles::console_message,
			sanguis::messages::adapted_types::string
		>
	>
>
console_print;

}
}
}

#endif
