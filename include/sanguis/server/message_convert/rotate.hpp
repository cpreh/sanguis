#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_ROTATE_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_ROTATE_HPP_INCLUDED

#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace message_convert
{

sanguis::messages::unique_ptr
rotate(
	sanguis::server::entities::with_body const &
);

}
}
}

#endif
