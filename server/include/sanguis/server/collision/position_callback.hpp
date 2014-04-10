#ifndef SANGUIS_SERVER_COLLISION_POSITION_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_POSITION_CALLBACK_HPP_INCLUDED

#include <sanguis/server/center_fwd.hpp>
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
		sanguis::server::center const &
	)
> position_callback;

}
}
}

#endif
