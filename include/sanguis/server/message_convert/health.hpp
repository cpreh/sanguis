#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_HEALTH_HPP_INCLUDED

#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace message_convert
{

sanguis::messages::unique_ptr
health(
	sanguis::server::entities::with_health const &
);

}
}
}

#endif
