#ifndef SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_POLYGON_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_DESERIALIZATION_POLYGON_HPP_INCLUDED

#include <sanguis/creator/geometry/polygon_fwd.hpp>
#include <sge/parse/json/array_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{
namespace deserialization
{

geometry::polygon const
polygon(
	sge::parse::json::array const &
);

}
}
}
}

#endif
