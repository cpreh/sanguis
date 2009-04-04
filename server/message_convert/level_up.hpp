#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_LEVEL_UP_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_LEVEL_UP_HPP_INCLUDED

#include "../entities/player_fwd.hpp"
#include "../../messages/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
level_up(
	entities::player const &);

}
}
}

#endif
