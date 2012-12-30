#ifndef SANGUIS_SERVER_COLLISION_BODY_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_CALLBACK_HPP_INCLUDED

#include <sanguis/server/collision/body_base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

typedef std::function<
	void(
		sanguis::server::collision::body_base &
	)
> body_callback;

}
}
}

#endif
