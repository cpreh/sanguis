#ifndef SANGUIS_SERVER_AI_ROTATE_TO_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ROTATE_TO_HPP_INCLUDED

#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

void
rotate_to(
	sanguis::server::entities::with_ai &,
	sanguis::server::angle
);

}
}
}

#endif
