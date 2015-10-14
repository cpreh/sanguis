#ifndef SANGUIS_LOAD_MODEL_RADIUS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_RADIUS_HPP_INCLUDED

#include <sanguis/collision/radius.hpp>
#include <sanguis/common/symbol.hpp>
#include <sanguis/model/cell_size_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

SANGUIS_COMMON_SYMBOL
sanguis::collision::radius
radius(
	sanguis::model::cell_size
);

}
}
}

#endif
