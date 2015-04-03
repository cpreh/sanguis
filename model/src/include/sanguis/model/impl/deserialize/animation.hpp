#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_HPP_INCLUDED

#include <sanguis/model/animation.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{
namespace deserialize
{

sanguis::model::animation
animation(
	sge::parse::json::object const &
);

}
}
}
}

#endif
