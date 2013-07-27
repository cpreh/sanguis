#ifndef SANGUIS_CREATOR_AUX_DESERIALIZATION_BACKGROUND_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_DESERIALIZATION_BACKGROUND_GRID_HPP_INCLUDED

#include <sanguis/creator/background_grid_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace deserialization
{

sanguis::creator::background_grid
background_grid(
	sge::parse::json::object const &
);

}
}
}
}

#endif
