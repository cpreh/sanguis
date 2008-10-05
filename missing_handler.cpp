#include "missing_handler.hpp"
#include "messages/base.hpp"
#include "exception.hpp"

#include <sge/iconv.hpp>
#include <sge/text.hpp>

#include <typeinfo>

boost::statechart::result sanguis::missing_handler(
	const sanguis::messages::base& b)
{
	throw exception(SGE_TEXT("Missing state handler: ")
		+ sge::iconv(typeid(b).name()));
}

