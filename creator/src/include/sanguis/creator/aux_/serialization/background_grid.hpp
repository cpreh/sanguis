#ifndef SANGUIS_CREATOR_AUX__SERIALIZATION_BACKGROUND_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__SERIALIZATION_BACKGROUND_GRID_HPP_INCLUDED

#include <sanguis/creator/background_grid_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace serialization
{

sge::parse::json::object
background_grid(
	sanguis::creator::background_grid const &
);

}
}
}
}

#endif
