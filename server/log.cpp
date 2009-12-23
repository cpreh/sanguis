#include "log.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::server::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			sanguis::log(),
			FCPPT_TEXT("server")
		)
	);
	return log_;
}
