#include "friend_name.hpp"
#include "../exception.hpp"
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::friend_name(
	friend_type::type const etype
)
{
	switch(etype)
	{
	case friend_type::spider:
		return FCPPT_TEXT("friendly_spider");
	case friend_type::sentry:
		return FCPPT_TEXT("sentry");
	case friend_type::size:
		break;
	}

	throw exception(
		FCPPT_TEXT("load::friend_name: missing loading code!")
	);
}
