#ifndef SANGUIS_MESSAGES_CONSOLE_PRINT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONSOLE_PRINT_HPP_INCLUDED

#include "make_class.hpp"
#include "string.hpp"
#include "make_message_id.hpp"
#include "types/message.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			messages::make_message_id<
				types::message::console_print
			>::type,
			majutsu::role<
				messages::string
			>
		>
	>
>::type console_print;

}
}

#endif
