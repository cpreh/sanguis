#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::ai::create_function const
sanguis::server::ai::create_simple(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
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
				fcppt::ref(
					_random_generator
				),
				boost::phoenix::arg_names::arg1,
				_link
			)
		);
}
