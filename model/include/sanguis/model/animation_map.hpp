#ifndef SANGUIS_MODEL_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/model/animation.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{

typedef
std::unordered_map<
	fcppt::string,
	sanguis::model::animation
>
animation_map;

}
}

#endif
