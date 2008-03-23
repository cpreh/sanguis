#include "missing_handler.hpp"
#include "messages/base.hpp"

#include <sge/iconv.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>

#include <typeinfo>

boost::statechart::result sanguis::missing_handler(
	const sanguis::messages::base& b)
{
	throw sge::exception(SGE_TEXT("Missing state handler: ")
		+ sge::iconv(typeid(b).name()));
}

