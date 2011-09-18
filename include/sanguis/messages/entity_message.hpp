#ifndef SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/entity_id.hpp>
#include <sanguis/messages/message_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		messages::message_type,
		majutsu::role<
			messages::entity_id,
			roles::entity_id
		>
	>
> entity_message;

}
}

#endif
