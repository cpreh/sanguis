#include "friend_name.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>

sge::string const
sanguis::load::friend_name(
	friend_type::type const etype)
{
	switch(etype) {
	case friend_type::spider:
		return SGE_TEXT("friendly_spider");
	case friend_type::sentry:
		return SGE_TEXT("sentry");
	default:
		throw exception(
			SGE_TEXT("load::friend_name: missing loading code!"));
	}
}
