#ifndef SANGUIS_SERVER_REMOVE_SIGHT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_REMOVE_SIGHT_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/with_id_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	void (
		sanguis::server::entities::with_id const &
	)
>
remove_sight_callback;

}
}

#endif
