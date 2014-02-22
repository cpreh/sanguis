#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_ANIMATION_DELAY_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_ANIMATION_DELAY_HPP_INCLUDED

#include <sanguis/model/optional_animation_delay.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::optional_animation_delay const
animation_delay(
	sge::parse::json::object const &
);

}
}
}
}

#endif
