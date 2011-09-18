#ifndef SANGUIS_CLIENT_PERK_LEVEL_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_LEVEL_MAP_HPP_INCLUDED

#include <sanguis/client/perk/level.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef std::map<
	sanguis::perk_type::type,
	perk::level
> level_map;

}
}
}

#endif
