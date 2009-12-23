#include "log.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::server::weapons::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("weapons")
		)
	);
	return log_;
}
