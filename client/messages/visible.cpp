#include "visible.hpp"

sanguis::client::messages::visible::visible(
	entity_id const id_,
	bool const visible_
)
:
	id_(id_),
	visible_(visible_)
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
