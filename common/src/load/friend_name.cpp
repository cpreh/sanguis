#include <sanguis/friend_type.hpp>
#include <sanguis/load/friend_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sanguis::load::friend_name(
	sanguis::friend_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::friend_type::spider:
		return FCPPT_TEXT("friendly_spider");
	case sanguis::friend_type::sentry:
		return FCPPT_TEXT("sentry");
	}

	FCPPT_ASSERT_UNREACHABLE;
}
