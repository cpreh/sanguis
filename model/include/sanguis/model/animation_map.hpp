#ifndef SANGUIS_MODEL_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::model
{

using
animation_map
=
std::unordered_map<
	sanguis::model::animation_name,
	sanguis::model::animation
>;

}

#endif
