#ifndef SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_SHAPE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_SHAPE_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/parse/json/array_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace deserialization
{

geometry::shape_container const
shape_container(
	sge::parse::json::array const &
);

}
}
}
}

#endif
