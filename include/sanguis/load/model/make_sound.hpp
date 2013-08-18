#ifndef SANGUIS_LOAD_MODEL_MAKE_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_SOUND_HPP_INCLUDED

#include <sanguis/load/model/optional_sound_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::optional_sound
make_sound(
	sge::parse::json::object const &,
	sanguis::load::resource::sounds const &
);

}
}
}

#endif
