#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_ROTATE_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_ROTATE_HPP_INCLUDED

#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
rotate(
	entities::with_body const &
);

}
}
}

#endif
