#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_SPEED_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_SPEED_HPP_INCLUDED

#include "../entities/movable_fwd.hpp"
#include "../../messages/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
speed(
	entities::movable const &
);

}
}
}

#endif
