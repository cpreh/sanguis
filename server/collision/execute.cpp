#include "execute.hpp"
#include "satellite.hpp"
#include "base.hpp"
#include <sge/function/object.hpp>

void
sanguis::server::collision::execute(
	sge::collision::satellite &a,
	sge::collision::satellite &b,
	execute_function const &function
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

	function(
		e0,
		e1
	);

	function(
		e1,
		e0
	);
}
