#ifndef SANGUIS_CREATOR_AUX_GENERATOR_SERIALIZATION_SHAPE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_GENERATOR_SERIALIZATION_SHAPE_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace generator
{
namespace serialization
{

sge::parse::json::array const
shape_container(
	sanguis::creator::geometry::shape_container const &
);

}
}
}
}
}

#endif
