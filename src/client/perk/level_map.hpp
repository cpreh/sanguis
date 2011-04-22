#ifndef SANGUIS_CLIENT_PERK_LEVEL_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_LEVEL_MAP_HPP_INCLUDED

#include "../level.hpp"
#include "../../perk_type.hpp"
#include <map>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef std::map<
	sanguis::perk_type::type,
	client::level
> level_map;

}
}
}

#endif
