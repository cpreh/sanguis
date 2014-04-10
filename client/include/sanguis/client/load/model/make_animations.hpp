#ifndef SANGUIS_CLIENT_LOAD_MODEL_MAKE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_MAKE_ANIMATIONS_HPP_INCLUDED

#include <sanguis/client/load/model/animation_map.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

sanguis::client::load::model::animation_map
make_animations(
	sanguis::model::weapon_category const &,
	sanguis::client::load::model::global_parameters const &
);

}
}
}
}

#endif
