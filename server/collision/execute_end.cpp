#include "execute_end.hpp"
#include "base.hpp"
#include <sge/function/object.hpp>
#include <tr1/functional>

sanguis::server::collision::execute_function const
sanguis::server::collision::execute_end()
{
	static execute_function const ret(
		std::tr1::bind(
			&base::collision_end,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);

	return ret;
}
