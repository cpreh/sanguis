#include "log.hpp"
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/log/logger.hpp>

sge::log::logger &
sanguis::log()
{
	static sge::log::logger log_(
		sge::cerr,
		SGE_TEXT("sanguis: "));
	log_.activate_hierarchie(
		sge::log::level::warning);
	return log_;
}
