#include <sanguis/server/events/disconnect.hpp>
#include <alda/net/id.hpp>


sanguis::server::events::disconnect::disconnect(
	alda::net::id const _id
)
:
	id_(
		_id
	)
{
}

sanguis::server::events::disconnect::disconnect(
	disconnect &&
)
noexcept
= default;

sanguis::server::events::disconnect::disconnect(
	disconnect const &
)
= default;

sanguis::server::events::disconnect &
sanguis::server::events::disconnect::operator=(
	disconnect &&
)
noexcept
= default;

sanguis::server::events::disconnect &
sanguis::server::events::disconnect::operator=(
	disconnect const &
)
= default;

sanguis::server::events::disconnect::~disconnect()
= default;

alda::net::id
sanguis::server::events::disconnect::id() const
{
	return
		id_;
}
