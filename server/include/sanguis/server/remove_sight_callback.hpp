#ifndef SANGUIS_SERVER_REMOVE_SIGHT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_REMOVE_SIGHT_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/with_id_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::server
{

using
remove_sight_callback
=
fcppt::function<
	void (
		sanguis::server::entities::with_id const &
	)
>;

}

#endif
