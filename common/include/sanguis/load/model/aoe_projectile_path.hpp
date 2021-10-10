#ifndef SANGUIS_LOAD_MODEL_AOE_PROJECTILE_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_AOE_PROJECTILE_PATH_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <sanguis/load/model/path.hpp>

namespace sanguis::load::model
{

SANGUIS_COMMON_SYMBOL
sanguis::load::model::path aoe_projectile_path(sanguis::aoe_projectile_type);

}

#endif
