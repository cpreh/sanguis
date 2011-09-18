#include <sanguis/server/events/disconnect.hpp>

sanguis::server::events::disconnect::disconnect(
	net::id const _id
)
:
	id_(_id)
{
}

sanguis::net::id
sanguis::server::events::disconnect::id() const
{
	return id_;
}
