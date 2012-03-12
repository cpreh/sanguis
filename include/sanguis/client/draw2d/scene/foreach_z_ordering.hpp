#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering.hpp>
#include <fcppt/foreach_enumerator_start_end.hpp>


#define SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING(\
	name,\
	start,\
	end\
)\
FCPPT_FOREACH_ENUMERATOR_START_END(\
	name,\
	sanguis::client::draw2d::z_ordering,\
	start,\
	static_cast<\
		sanguis::client::draw2d::z_ordering::type\
	>(\
		end + 1\
	)\
)

#endif
