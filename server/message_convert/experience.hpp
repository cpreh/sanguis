#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_EXPERIENCE_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_EXPERIENCE_HPP_INCLUDED

#include "../entities/player_fwd.hpp"
#include "../../messages/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
experience(
	entities::player const &
);

}
}
}

#endif
