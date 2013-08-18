#ifndef SANGUIS_LOAD_MODEL_MAKE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_ANIMATIONS_HPP_INCLUDED

#include <sanguis/load/model/animation_map.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::animation_map
make_animations(
	sge::parse::json::object const &,
	sanguis::load::model::global_parameters const &
);

}
}
}

#endif
