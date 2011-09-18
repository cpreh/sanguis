#ifndef SANGUIS_SERVER_PERKS_TREE_MAX_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_MAX_LEVEL_HPP_INCLUDED

#include <sanguis/server/level.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

FCPPT_MAKE_STRONG_TYPEDEF(
	server::level::value_type,
	max_level
);

}
}
}
}

#endif
