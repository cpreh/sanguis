#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_ALIGN_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_ALIGN_TYPE_HPP_INCLUDED

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
namespace align_type
{
enum type 
{ 
	none,
	to_center,
	random,
	size 
};
}

fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	align_type::type
);

fcppt::io::istream &
operator>>(
	fcppt::io::istream &,
	align_type::type &
);

}
}
}
}

#endif
