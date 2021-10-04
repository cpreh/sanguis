#ifndef SANGUIS_SERVER_SOURCE_WORLD_ID_HPP_INCLUDED
#define SANGUIS_SERVER_SOURCE_WORLD_ID_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::world_id,
	source_world_id
);

}

#endif
