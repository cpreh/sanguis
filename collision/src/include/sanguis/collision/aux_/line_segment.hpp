#ifndef SANGUIS_COLLISION_AUX__LINE_SEGMENT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__LINE_SEGMENT_HPP_INCLUDED

#include <sanguis/collision/aux_/dir.hpp>
#include <sanguis/collision/aux_/line_segment_fwd.hpp>
#include <sanguis/collision/aux_/pos.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

class line_segment
{
public:
	line_segment(
		sanguis::collision::aux_::pos const &,
		sanguis::collision::aux_::dir const &
	);

	sanguis::collision::aux_::pos const &
	pos() const;

	sanguis::collision::aux_::dir const &
	dir() const;
private:
	sanguis::collision::aux_::pos pos_;

	sanguis::collision::aux_::dir dir_;
};

}
}
}

#endif
