#include "log.hpp"
#include <sge/log/object.hpp>
#include <sge/log/parameters/root.hpp>
#include <sge/log/parameters/all.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>

sge::log::object &
sanguis::log()
{
	static sge::log::object log_(
		sge::log::parameters::root(
			sge::cerr
		)
		.prefix(
			SGE_TEXT("sanguis: ")
		)
		.enabled(
			true
		)
		.level(
			sge::log::level::warning
		)
		.create()
	);
	return log_;
}
