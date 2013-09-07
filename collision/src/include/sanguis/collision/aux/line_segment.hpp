#ifndef SANGUIS_COLLISION_AUX_LINE_SEGMENT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_LINE_SEGMENT_HPP_INCLUDED

#include <sanguis/collision/aux/dir.hpp>
#include <sanguis/collision/aux/line_segment_fwd.hpp>
#include <sanguis/collision/aux/pos.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{

class line_segment
{
public:
	line_segment(
		sanguis::collision::aux::pos const &,
		sanguis::collision::aux::dir const &
	);

	sanguis::collision::aux::pos const &
	pos() const;

	sanguis::collision::aux::dir const &
	dir() const;
private:
	sanguis::collision::aux::pos pos_;

	sanguis::collision::aux::dir dir_;
};

}
}
}

#endif
