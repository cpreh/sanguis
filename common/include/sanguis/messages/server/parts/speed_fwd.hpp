#ifndef SANGUIS_MESSAGES_SERVER_PARTS_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_SPEED_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/roles/speed.hpp>
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
	sanguis::messages::adapted_types::vector2,
	sanguis::messages::roles::speed
>
speed;

}
}
}
}

#endif
