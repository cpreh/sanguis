#ifndef SANGUIS_COLLISION_AUX__INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/aux_/dir.hpp>
#include <sanguis/collision/aux_/intersection_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

class intersection
{
public:
	explicit
	intersection(
		sanguis::collision::aux_::dir const &
	);

	sanguis::collision::aux_::dir const &
	dir() const;
private:
	sanguis::collision::aux_::dir dir_;
};

}
}
}

#endif
