#include "make.hpp"
#include "debug.hpp"
#include "wave.hpp"
#include "../../exception.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::waves::unique_ptr
sanguis::server::waves::make(
	fcppt::string const &name
)
{
	// TODO: add more!
	if(
		name == FCPPT_TEXT("debug")
	)
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					debug
				>()
			);
	throw
		exception(
			FCPPT_TEXT("Invalid wave ")
			+ name
		);
}
