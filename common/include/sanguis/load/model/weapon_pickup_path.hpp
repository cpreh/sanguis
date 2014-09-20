#ifndef SANGUIS_LOAD_MODEL_WEAPON_PICKUP_PATH_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_PICKUP_PATH_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <sanguis/load/model/path.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

SANGUIS_COMMON_SYMBOL
sanguis::load::model::path
weapon_pickup_path(
	sanguis::weapon_type
);

}
}
}

#endif
