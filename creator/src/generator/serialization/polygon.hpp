#ifndef SANGUIS_CREATOR_GENERATOR_SERIALIZATION_POLYGON_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_SERIALIZATION_POLYGON_HPP_INCLUDED

#include <sanguis/creator/geometry/polygon_fwd.hpp>
#include <sge/parse/json/array_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace serialization
{

sge::parse::json::array const
polygon(
	geometry::polygon const &
);

}
}
}
}

#endif
