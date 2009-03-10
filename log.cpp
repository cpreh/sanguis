#include "log.hpp"
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <sge/log/logger.hpp>

sge::log::logger &
sanguis::log()
{
	static sge::log::logger log_(
		sge::cerr,
		SGE_TEXT("sanguis: "),
		true,
		sge::log::level::debug
	);
	return log_;
}
