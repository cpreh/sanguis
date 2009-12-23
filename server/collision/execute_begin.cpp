#include "execute_begin.hpp"
#include "base.hpp"
#include <fcppt/function/object.hpp>
#include <tr1/functional>

sanguis::server::collision::execute_function const
sanguis::server::collision::execute_begin()
{
	static execute_function const ret(
		std::tr1::bind(
			&base::collision_begin,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);

	return ret;
}
