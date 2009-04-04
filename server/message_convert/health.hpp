#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_HEALTH_HPP_INCLUDED

#include "../entities/entity_fwd.hpp"
#include "../../messages/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
health(
	entities::entity const &);

}
}
}

#endif
