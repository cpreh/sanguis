#include "log.hpp"
#include "../log.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <fcppt/text.hpp>

sge::log::object &
sanguis::net::log()
{
	static sge::log::object l(
		sge::log::parameters::inherited(
			sanguis::log(),
			FCPPT_TEXT("net")
		)
	);

	return l;
}
