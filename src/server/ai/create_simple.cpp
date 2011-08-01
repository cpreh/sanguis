#include "create_simple.hpp"
#include "simple.hpp"
#include "../entities/auto_weak_link.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/cref.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sanguis::server::ai::create_function const
sanguis::server::ai::create_simple(
	sanguis::diff_clock const &_diff_clock,
	entities::auto_weak_link const &_link
)
{
	return
		boost::phoenix::construct<
			ai::unique_ptr
		>(
			boost::phoenix::new_<
				ai::simple
			>(
				fcppt::cref(
					_diff_clock
				),
				boost::phoenix::arg_names::arg1,
				_link
			)
		);
}
