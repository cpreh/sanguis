#ifndef SANGUIS_SERVER_COLLISION_BODY_EXIT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_EXIT_CALLBACK_HPP_INCLUDED

#include <sanguis/server/collision/body_callback.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::collision::body_callback,
	body_exit_callback
);

}
}
}

#endif
