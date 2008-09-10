#include "log.hpp"
#include "../log.hpp"
#include <sge/log/logger.hpp>
#include <sge/text.hpp>

sge::log::logger &
sanguis::server::weapons::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("weapons: "));
	return log_;
}
