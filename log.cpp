#include "log.hpp"
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/once.hpp>
#include <sge/log/logger.hpp>

sge::log::logger &
sanguis::log()
{
	static sge::log::logger log_(
		sge::cerr,
		SGE_TEXT("sanguis: "));
	return log_;
}
