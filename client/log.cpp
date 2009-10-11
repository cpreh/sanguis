#include "log.hpp"
#include "../log.hpp"
#include <sge/log/object.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/text.hpp>

sge::log::object &
sanguis::client::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			sanguis::log(),
			SGE_TEXT("client: ")
		)
	);
	return log_;
}
