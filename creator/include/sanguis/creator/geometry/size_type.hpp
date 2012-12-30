#ifndef SANGUIS_CREATOR_GEOMETRY_SIZE_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_SIZE_TYPE_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace geometry
{

typedef std::make_unsigned<
	sanguis::creator::geometry::unit
>::type size_type;

}
}
}

#endif
