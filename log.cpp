#include "log.hpp"
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/once.hpp>
#include <sge/log/logger.hpp>

namespace
{

void configure(
	sge::log::logger &);

}

sge::log::logger &
sanguis::log()
{
	static sge::log::logger log_(
		sge::cerr,
		SGE_TEXT("sanguis: "));
	configure(log_);
	return log_;
}

namespace
{

void configure(
	sge::log::logger &l)
{
	SGE_FUNCTION_ONCE

	l.activate_hierarchy(
		sge::log::level::warning);
}

}
