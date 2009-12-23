#include "log.hpp"
#include "../log.hpp"
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::client::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			sanguis::log(),
			FCPPT_TEXT("client")
		)
	);
	return log_;
}
