#ifndef SANGUIS_LOAD_AOE_PROJECTILE_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_AOE_PROJECTILE_NAME_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <fcppt/string.hpp>

namespace sanguis::load
{

SANGUIS_COMMON_SYMBOL
fcppt::string aoe_projectile_name(sanguis::aoe_projectile_type);

}

#endif
