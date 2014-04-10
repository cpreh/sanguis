#ifndef SANGUIS_SERVER_AI_PATHING_IS_VISIBLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_IS_VISIBLE_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace pathing
{

bool
is_visible(
	sanguis::creator::grid const &,
	sanguis::creator::pos,
	sanguis::creator::pos
);

}
}
}
}

#endif
