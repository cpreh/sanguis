#ifndef SANGUIS_SERVER_GLOBAL_DEST_WORLD_PAIR_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_DEST_WORLD_PAIR_HPP_INCLUDED

#include <sanguis/creator/opening.hpp>
#include <sanguis/server/dest_world_id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

typedef
std::pair<
	sanguis::server::dest_world_id,
	sanguis::creator::opening
>
dest_world_pair;

}
}
}

#endif
