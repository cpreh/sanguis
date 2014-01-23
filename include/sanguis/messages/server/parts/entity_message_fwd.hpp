#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_MESSAGE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_MESSAGE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/entity_id.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <alda/message/id_binding.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
majutsu::composite<
	boost::mpl::vector2<
		alda::message::id_binding,
		majutsu::role<
			sanguis::messages::adapted_types::entity_id,
			sanguis::messages::roles::entity_id
		>
	>
>
entity_message;

}
}
}
}

#endif
