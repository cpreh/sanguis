#ifndef SANGUIS_DRAW_PARTICLE_MOVEMENT_TYPE_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_MOVEMENT_TYPE_HPP_INCLUDED

#include <sge/ostream.hpp>
#include <sge/istream.hpp>

namespace sanguis 
{
namespace draw
{
namespace particle
{

namespace movement_type
{
enum type
{
	random,
	expanding,
	shrinking,
	size
};
}

sge::ostream &
operator<<(
	sge::ostream &,
	movement_type::type);

sge::istream &
operator>>(
	sge::istream &,
	movement_type::type &);

}
}
}

#endif
