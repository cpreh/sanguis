#ifndef SANGUIS_SERVER_COLLISION_TEST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TEST_HPP_INCLUDED

#include <sge/collision/satellite_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

bool
test(
	sge::collision::satellite const &,
	sge::collision::satellite const &);

}
}
}

#endif
