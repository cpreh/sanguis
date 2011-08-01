#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_INTERVAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_INTERVAL_HPP_INCLUDED

#include "../../../duration.hpp"
#include <fcppt/chrono/duration_decl.hpp>
#include <fcppt/make_strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace spawns
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	interval
);

}
}
}
}

#endif
