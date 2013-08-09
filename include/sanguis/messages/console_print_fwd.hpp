#ifndef SANGUIS_MESSAGES_CONSOLE_PRINT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONSOLE_PRINT_FWD_HPP_INCLUDED

#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/make_message_id_fwd.hpp>
#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::make_message_id<
				sanguis::messages::types::message::console_print
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string
			>
		>
	>
>
console_print;

}
}

#endif
