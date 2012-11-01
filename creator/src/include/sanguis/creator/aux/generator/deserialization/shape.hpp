#ifndef SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_SHAPE_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_SHAPE_HPP_INCLUDED

#include <sanguis/creator/geometry/shape_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace generator
{
namespace deserialization
{

sanguis::creator::geometry::shape const
shape(
	sge::parse::json::object const &
);

}
}
}
}
}

#endif
