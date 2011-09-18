#ifndef SANGUIS_MESSAGES_LEVEL_UP_HPP_INCLUDED
#define SANGUIS_MESSAGES_LEVEL_UP_HPP_INCLUDED

#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/bind_entity_message.hpp>
#include <sanguis/messages/level.hpp>
#include <sanguis/messages/make_class.hpp>
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
		boost::mpl::vector2<
			messages::bind_entity_message<
				types::message::level_up
			>::type,
			majutsu::role<
				messages::level
			>
		>
	>
>::type level_up;

}
}

#endif
