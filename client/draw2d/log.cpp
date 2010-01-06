#include "log.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::client::draw2d::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			client::log(),
			FCPPT_TEXT("draw2d")
		)
	);

	return log_;
}
