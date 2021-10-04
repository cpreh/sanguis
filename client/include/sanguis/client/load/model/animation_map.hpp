#ifndef SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::load::model
{

using
animation_map
=
std::map<
	sanguis::client::load::animation_type,
	sanguis::client::load::model::animation_unique_ptr
>;

}

#endif
