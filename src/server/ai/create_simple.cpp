#include "create_simple.hpp"
#include "simple.hpp"
#include "../entities/auto_weak_link.hpp"
#include <fcppt/function/object.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sanguis::server::ai::create_function const
sanguis::server::ai::create_simple(
	entities::auto_weak_link const &_link
)
{
	return
		boost::phoenix::construct<
			ai::unique_ptr
		>(
			boost::phoenix::new_<
				simple
			>(
				boost::phoenix::arg_names::arg1,
				_link
			)
		);
}
