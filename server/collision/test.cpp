#include "test.hpp"
#include "base.hpp"
#include "satellite.hpp"

bool
sanguis::server::collision::test(
	sge::collision::satellite const &a,
	sge::collision::satellite const &b)
{
	base const
		&e0(
			dynamic_cast<
				satellite const &
			>(a).base()
		),
	        &e1(
			dynamic_cast<
				satellite const &
			>(b).base()
		);
	
	// TODO: tribool!	
	return e0.can_collide_with(e1) || e1.can_collide_with(e0);
}
