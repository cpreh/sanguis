#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_MOVEMENT_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_MOVEMENT_TYPE_HPP_INCLUDED

#include <fcppt/io/ostream.hpp>
#include <fcppt/io/istream.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
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
}

#endif
