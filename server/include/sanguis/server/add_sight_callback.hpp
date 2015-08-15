#ifndef SANGUIS_SERVER_ADD_SIGHT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ADD_SIGHT_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/server/entities/with_id_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	void (
		sanguis::server::entities::with_id const &,
		sanguis::collision::world::created
	)
>
add_sight_callback;

}
}

#endif
