#ifndef SANGUIS_SERVER_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_CIRCLE_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/math/sphere/circle.hpp>


namespace sanguis
{
namespace server
{

typedef fcppt::math::sphere::circle<
	sanguis::server::space_unit
>::type circle;

}
}

#endif
