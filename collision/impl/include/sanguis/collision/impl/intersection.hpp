#ifndef SANGUIS_COLLISION_IMPL_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/intersection_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

class intersection
{
public:
	explicit
	intersection(
		sanguis::collision::impl::dir
	);

	[[nodiscard]]
	sanguis::collision::impl::dir const &
	dir() const;
private:
	sanguis::collision::impl::dir dir_;
};

}
}
}

#endif
