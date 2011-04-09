#ifndef SANGUIS_SERVER_COLLISION_BODY_ENTER_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_ENTER_CALLBACK_HPP_INCLUDED

#include "body_callback.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

FCPPT_MAKE_STRONG_TYPEDEF(
	collision::body_callback,
	body_enter_callback
);

}
}
}

#endif
