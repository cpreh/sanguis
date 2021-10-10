#ifndef SANGUIS_LOAD_MODEL_PICKUP_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PICKUP_PATH_HPP_INCLUDED

#include <sanguis/pickup_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <sanguis/load/model/path.hpp>

namespace sanguis::load::model
{

SANGUIS_COMMON_SYMBOL
sanguis::load::model::path pickup_path(sanguis::pickup_type);

}

#endif
