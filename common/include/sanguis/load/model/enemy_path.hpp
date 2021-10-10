#ifndef SANGUIS_LOAD_MODEL_ENEMY_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ENEMY_PATH_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/load/model/path.hpp>

namespace sanguis::load::model
{

SANGUIS_COMMON_SYMBOL
sanguis::load::model::path enemy_path(sanguis::creator::enemy_type);

}

#endif
