#include "log.hpp"
#include "../log.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <fcppt/text.hpp>

sge::log::object &
sanguis::load::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			sanguis::log(),
			FCPPT_TEXT("load")
		)
	);
	return log_;
}
