#include "execute_end.hpp"
#include "base.hpp"
#include <boost/bind.hpp>

sanguis::server::collision::execute_function const
sanguis::server::collision::execute_end()
{
	static execute_function const ret(
		boost::bind(
			&base::collision_end,
			_1,
			_2
		)
	);

	return ret;
}
