#ifndef SANGUIS_COLLISION_LINE_SEGMENT_HPP_INCLUDED
#define SANGUIS_COLLISION_LINE_SEGMENT_HPP_INCLUDED

#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/line_segment_fwd.hpp>
#include <sanguis/collision/pos.hpp>


namespace sanguis
{
namespace collision
{

class line_segment
{
public:
	line_segment(
		sanguis::collision::pos const &,
		sanguis::collision::dir const &
	);

	sanguis::collision::pos const &
	pos() const;

	sanguis::collision::dir const &
	dir() const;
private:
	sanguis::collision::pos pos_;

	sanguis::collision::dir dir_;
};

}
}

#endif
