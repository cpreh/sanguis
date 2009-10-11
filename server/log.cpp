#include "log.hpp"
#include "../log.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/text.hpp>

sge::log::object &
sanguis::server::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			sanguis::log(),
			SGE_TEXT("server: ")
		)
	);
	return log_;
}
