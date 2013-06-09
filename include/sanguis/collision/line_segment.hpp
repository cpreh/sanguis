#ifndef SANGUIS_COLLISION_LINE_SEGMENT_HPP_INCLUDED
#define SANGUIS_COLLISION_LINE_SEGMENT_HPP_INCLUDED

#include <sanguis/collision/line_segment_fwd.hpp>
#include <sanguis/collision/vector2.hpp>


namespace sanguis
{
namespace collision
{

class line_segment
{
public:
	line_segment(
		sanguis::collision::vector2 const &pos,
		sanguis::collision::vector2 const &dir
	);

	sanguis::collision::vector2 const &
	pos() const;

	sanguis::collision::vector2 const &
	dir() const;
private:
	sanguis::collision::vector2 pos_;

	sanguis::collision::vector2 dir_;
};

}
}

#endif
