#ifndef SANGUIS_MESSAGES_CONNECT_STATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONNECT_STATE_HPP_INCLUDED

#include "make_message_id.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "roles/connect_state.hpp"
#include "types/message.hpp"
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef make_class<
	majutsu::composite<
		boost::mpl::vector2<
			make_message_id<
				types::message::connect_state
			>::type,
			majutsu::role<
				enum_,
				roles::connect_state
			>
		>
	>
>::type connect_state;

}
}

#endif
