#ifndef SANGUIS_CREATOR_AUX_SERIALIZATION_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_SERIALIZATION_GRID_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace serialization
{

sge::parse::json::object
grid(
	sanguis::creator::grid const &
);

}
}
}
}

#endif
