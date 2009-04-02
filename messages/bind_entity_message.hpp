#ifndef SANGUIS_MESSAGES_BIND_ENTITY_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BIND_ENTITY_MESSAGE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types/message.hpp"
#include <majutsu/bind.hpp>
#include <majutsu/constant.hpp>
#include <majutsu/placeholder.hpp>
#include <sge/restrict_typedef_struct.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

template<
	types::message::type Msg
>
struct bind_entity_message {
	typedef majutsu::bind<
		entity_message,
		boost::mpl::vector<
			majutsu::constant<
				types::message::type,
				Msg
			>,
			majutsu::placeholder
		>
	> type;

	SGE_RESTRICT_TYPEDEF_STRUCT(bind_entity_message)
};

}
}

#endif
