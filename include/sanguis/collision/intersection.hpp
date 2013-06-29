#ifndef SANGUIS_COLLISION_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection_fwd.hpp>
#include <sanguis/collision/unit.hpp>


namespace sanguis
{
namespace collision
{

class intersection
{
public:
	intersection(
		sanguis::collision::dir const &,
		sanguis::collision::unit
	);

	sanguis::collision::dir const &
	dir() const;

	sanguis::collision::unit
	pos() const;
private:
	sanguis::collision::dir dir_;

	sanguis::collision::unit pos_;
};

}
}

#endif
