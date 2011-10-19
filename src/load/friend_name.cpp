#include <sanguis/load/friend_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::friend_name(
	friend_type::type const _type
)
{
	switch(
		_type
	)
	{
	case friend_type::spider:
		return FCPPT_TEXT("friendly_spider");
	case friend_type::sentry:
		return FCPPT_TEXT("sentry");
	case friend_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
