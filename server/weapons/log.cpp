#include "log.hpp"
#include "../log.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/text.hpp>

sge::log::object &
sanguis::server::weapons::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			server::log(),
			SGE_TEXT("weapons")
		)
	);
	return log_;
}
