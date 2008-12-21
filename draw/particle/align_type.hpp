#ifndef SANGUIS_DRAW_PARTICLE_ALIGN_TYPE_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_ALIGN_TYPE_HPP_INCLUDED

#include <sge/ostream.hpp>
#include <sge/istream.hpp>

namespace sanguis
{
namespace draw
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

sge::ostream &
operator<<(
	sge::ostream &,
	align_type::type);

sge::istream &
operator>>(
	sge::istream &,
	align_type::type &);

}
}
}

#endif
