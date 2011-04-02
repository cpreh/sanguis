#ifndef SANGUIS_SERVER_PERKS_REQUIRED_PARENT_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_REQUIRED_PARENT_LEVEL_HPP_INCLUDED

#include "../level.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

FCPPT_MAKE_STRONG_TYPEDEF(
	server::level::value_type,
	required_parent_level
);

}
}
}

#endif
