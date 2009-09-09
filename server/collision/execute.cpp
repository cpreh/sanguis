#include "execute.hpp"
#include "base.hpp"
#include "satellite.hpp"

void
sanguis::server::collision::execute(
	sge::collision::satellite &a,
	sge::collision::satellite &b
)
{
	base
		&e0(
			dynamic_cast<
				satellite &
			>(a).base()
		),
		&e1(
			dynamic_cast<
				satellite &
			>(b).base()
		);
	
	e0.collision(e1);
	e1.collision(e0);
}
