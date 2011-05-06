#ifndef SANGUIS_CREATOR_GENERATOR_SERIALIZATION_VERTEX_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_SERIALIZATION_VERTEX_HPP_INCLUDED

#include <sanguis/creator/geometry/vertex_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace serialization
{

sge::parse::json::object const
vertex(
	geometry::vertex const &
);

}
}
}
}

#endif
