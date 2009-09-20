#include "execute_begin.hpp"
#include "base.hpp"
#include <boost/bind.hpp>

sanguis::server::collision::execute_function const
sanguis::server::collision::execute_begin()
{
	static execute_function const ret(
		boost::bind(
			&base::collision_begin,
			_1,
			_2
		)
	);

	return ret;
}
