#ifndef SANGUIS_CREATOR_AUX__DESERIALIZATION_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__DESERIALIZATION_GRID_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace deserialization
{

sanguis::creator::grid
grid(
	sge::parse::json::object const &
);

}
}
}
}

#endif