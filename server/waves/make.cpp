#include "make.hpp"
#include "debug.hpp"
#include "wave.hpp"
#include "../../exception.hpp"
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::waves::wave_auto_ptr
sanguis::server::waves::make(
	fcppt::string const &name
)
{
	// TODO: add more!
	if(
		name == FCPPT_TEXT("debug")
	)
		return
			wave_auto_ptr(
				new debug()
			);
			/*fcppt::make_auto_ptr<
				debug
			>();*/
	throw
		exception(
			FCPPT_TEXT("Invalid wave ")
			+ name
		);
}
