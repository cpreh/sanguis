#ifndef SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_VERTEX_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_VERTEX_HPP_INCLUDED

#include <sanguis/creator/geometry/vertex_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace deserialization
{

geometry::vertex const
vertex(
	sge::parse::json::object const &
);

}
}
}
}

#endif
