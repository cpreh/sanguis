#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_AURAS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_AURAS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/aura_type_vector_fwd.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <majutsu/role_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
majutsu::role<
	sanguis::messages::adapted_types::aura_type_vector,
	sanguis::messages::roles::aura_type_container
>
add_with_auras;

}
}
}
}

#endif
