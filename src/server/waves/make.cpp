#include <sanguis/server/waves/make.hpp>
#include <sanguis/server/waves/debug.hpp>
#include <sanguis/server/waves/wave.hpp>
#include <sanguis/exception.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::waves::unique_ptr
sanguis::server::waves::make(
	sanguis::diff_clock const &_diff_clock,
	fcppt::string const &_name
)
{
	// TODO: add more!
	if(
		_name == FCPPT_TEXT("debug")
	)
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					debug
				>(
					fcppt::cref(
						_diff_clock
					)
				)
			);
	throw
		sanguis::exception(
			FCPPT_TEXT("Invalid wave ")
			+ _name
		);
}
