#ifndef SANGUIS_SERVER_PERKS_DIFF_FACTOR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_DIFF_FACTOR_HPP_INCLUDED

#include "level_type.hpp"
#include "level_diff.hpp"
#include "../entities/property/value.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

entities::property::value
diff_factor(
	entities::property::value (*)(level_type),
	level_type,
	level_diff
);

}
}
}

#endif
