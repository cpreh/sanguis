#include "log.hpp"
#include "../log.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/text.hpp>

sge::log::object &
sanguis::net::log()
{
	static sge::log::object l(
		sge::log::parameters::inherited(
			sanguis::log(),
			SGE_TEXT("net")
		)
	);

	return l;
}
