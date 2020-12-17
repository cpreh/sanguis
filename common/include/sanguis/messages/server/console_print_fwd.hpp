#ifndef SANGUIS_MESSAGES_SERVER_CONSOLE_PRINT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CONSOLE_PRINT_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/console_message.hpp>
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
console_print
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::console_print
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::console_message,
			sanguis::messages::adapted_types::string
		>
	>
>;

}
}
}

#endif
