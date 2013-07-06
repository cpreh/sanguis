#ifndef SANGUIS_COLLISION_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection_fwd.hpp>


namespace sanguis
{
namespace collision
{

class intersection
{
public:
	explicit
	intersection(
		sanguis::collision::dir const &
	);

	sanguis::collision::dir const &
	dir() const;
private:
	sanguis::collision::dir dir_;
};

}
}

#endif
