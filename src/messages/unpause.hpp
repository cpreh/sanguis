#ifndef SANGUIS_MESSAGES_UNPAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_UNPAUSE_HPP_INCLUDED

#include "types/message.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			messages::make_message_id<
				types::message::unpause
			>::type
		>
	>
>::type unpause;

}
}

#endif
