#ifndef SANGUIS_DRAW_PARTICLE_MOVEMENT_TYPE_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_MOVEMENT_TYPE_HPP_INCLUDED

#include <fcppt/io/ostream.hpp>
#include <fcppt/io/istream.hpp>

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

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	movement_type::type);

fcppt::io::istream &
operator>>(
	fcppt::io::istream &,
	movement_type::type &);

}
}
}

#endif
