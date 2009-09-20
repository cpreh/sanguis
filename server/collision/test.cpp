#include "test.hpp"
#include "base.hpp"
#include "satellite.hpp"
#include <boost/logic/tribool.hpp>

bool
sanguis::server::collision::test(
	sge::collision::satellite const &a,
	sge::collision::satellite const &b
)
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
	
	boost::logic::tribool const 
		b0(
			e0.can_collide_with(e1)
		),
		b1(
			e1.can_collide_with(e0)
		);
	
	return !b0 || !b1
		? false
		: static_cast<bool>(b0 || b1);
}
