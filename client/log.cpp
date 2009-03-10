#include "log.hpp"
#include "../log.hpp"
#include <sge/log/logger.hpp>
#include <sge/text.hpp>

sge::log::logger &
sanguis::client::log()
{
	static sge::log::logger log_(
		sanguis::log(),
		SGE_TEXT("client: "),
		true
	);
	return log_;
}
