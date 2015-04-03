#ifndef SANGUIS_COLLISION_IMPL_LINE_SEGMENT_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_LINE_SEGMENT_HPP_INCLUDED

#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/line_segment_fwd.hpp>
#include <sanguis/collision/impl/pos.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

class line_segment
{
public:
	line_segment(
		sanguis::collision::impl::pos const &,
		sanguis::collision::impl::dir const &
	);

	sanguis::collision::impl::pos const &
	pos() const;

	sanguis::collision::impl::dir const &
	dir() const;
private:
	sanguis::collision::impl::pos pos_;

	sanguis::collision::impl::dir dir_;
};

}
}
}

#endif
