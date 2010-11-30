#include "visible.hpp"

sanguis::client::messages::visible::visible(
	entity_id const _id,
	bool const _visible
)
:
	id_(_id),
	visible_(_visible)
{}

sanguis::entity_id
sanguis::client::messages::visible::id() const
{
	return id_;
}

bool
sanguis::client::messages::visible::get() const
{
	return visible_;
}
