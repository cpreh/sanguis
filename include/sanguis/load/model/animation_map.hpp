#ifndef SANGUIS_LOAD_MODEL_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/load/animation_type.hpp>
#include <sanguis/load/model/animation_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

typedef std::map<
	sanguis::load::animation_type,
	sanguis::load::model::animation_unique_ptr
> animation_map;

}
}
}

#endif
