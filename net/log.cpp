#include "log.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::net::log()
{
	static fcppt::log::object l(
		fcppt::log::parameters::inherited(
			sanguis::log(),
			FCPPT_TEXT("net")
		)
	);

	return l;
}
