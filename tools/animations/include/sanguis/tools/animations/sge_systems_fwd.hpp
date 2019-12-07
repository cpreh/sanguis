#ifndef SANGUIS_TOOLS_ANIMATIONS_SGE_SYSTEMS_FWD_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_SGE_SYSTEMS_FWD_HPP_INCLUDED

#include <sge/systems/instance_fwd.hpp>
#include <sge/systems/with_image2d_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

typedef
sge::systems::instance<
	sge::systems::with_image2d
>
sge_systems;

}
}
}

#endif
