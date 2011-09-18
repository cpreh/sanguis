#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_SPEED_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_SPEED_HPP_INCLUDED

#include <sanguis/server/entities/with_velocity_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
speed(
	entities::with_velocity const &
);

}
}
}

#endif
