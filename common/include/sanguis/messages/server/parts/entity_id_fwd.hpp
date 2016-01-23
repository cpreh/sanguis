#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_ID_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/entity_id_fwd.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <majutsu/role_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

using
entity_id
=
majutsu::role<
	sanguis::messages::adapted_types::entity_id,
	sanguis::messages::roles::entity_id
>;

}
}
}
}

#endif
