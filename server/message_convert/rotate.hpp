#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_ROTATE_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_ROTATE_HPP_INCLUDED

#include "../entities/base_fwd.hpp"
#include "../../messages/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
rotate(
	entities::base const &
);

}
}
}

#endif
