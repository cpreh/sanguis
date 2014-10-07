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

alda::net::id const
sanguis::server::events::disconnect::id() const
{
	return
		id_;
}
