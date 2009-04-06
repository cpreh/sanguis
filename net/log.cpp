#include "log.hpp"
#include "../log.hpp"
#include <sge/text.hpp>

sge::log::logger &sanguis::net::log()
{
	static sge::log::logger l(
		sanguis::log(),
		SGE_TEXT("net: "),
		false);
	return l;
}
