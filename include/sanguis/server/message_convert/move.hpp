#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_MOVE_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_MOVE_HPP_INCLUDED

#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/entities/with_velocity_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace message_convert
{

sanguis::messages::unique_ptr
move(
	sanguis::server::entities::with_velocity const &
);

}
}
}

#endif
