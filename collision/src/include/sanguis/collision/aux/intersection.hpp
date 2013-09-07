#ifndef SANGUIS_COLLISION_AUX_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/aux/dir.hpp>
#include <sanguis/collision/aux/intersection_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{

class intersection
{
public:
	explicit
	intersection(
		sanguis::collision::aux::dir const &
	);

	sanguis::collision::aux::dir const &
	dir() const;
private:
	sanguis::collision::aux::dir dir_;
};

}
}
}

#endif
