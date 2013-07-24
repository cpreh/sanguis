#ifndef SANGUIS_SERVER_GLOBAL_WORLD_ID_PAIR_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_ID_PAIR_HPP_INCLUDED

#include <sanguis/server/dest_world_id.hpp>
#include <sanguis/server/source_world_id.hpp>
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
	sanguis::server::source_world_id,
	sanguis::server::dest_world_id
>
world_id_pair;

}
}
}

#endif
