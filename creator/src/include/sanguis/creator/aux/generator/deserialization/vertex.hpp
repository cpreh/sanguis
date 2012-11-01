#ifndef SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_VERTEX_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_VERTEX_HPP_INCLUDED

#include <sanguis/creator/geometry/vertex_fwd.hpp>
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

sanguis::creator::geometry::vertex const
vertex(
	sge::parse::json::object const &
);

}
}
}
}
}

#endif
