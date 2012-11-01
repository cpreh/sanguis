#ifndef SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_POLYGON_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_GENERATOR_DESERIALIZATION_POLYGON_HPP_INCLUDED

#include <sanguis/creator/geometry/polygon_fwd.hpp>
#include <sge/parse/json/array_fwd.hpp>


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

sanguis::creator::geometry::polygon const
polygon(
	sge::parse::json::array const &
);

}
}
}
}
}

#endif
