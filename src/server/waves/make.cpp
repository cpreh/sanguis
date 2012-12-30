#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/waves/debug.hpp>
#include <sanguis/server/waves/make.hpp>
#include <sanguis/server/waves/wave.hpp>
#include <sanguis/server/waves/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sanguis::server::waves::unique_ptr
sanguis::server::waves::make(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	fcppt::string const &_name
)
{
	// TODO: add more!
	if(
		_name == FCPPT_TEXT("debug")
	)
		return
			fcppt::make_unique_ptr<
				sanguis::server::waves::debug
			>(
				_diff_clock,
				_random_generator
			);
	throw
		sanguis::exception(
			FCPPT_TEXT("Invalid wave ")
			+ _name
		);
}
