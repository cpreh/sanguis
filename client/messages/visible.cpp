#include "visible.hpp"

sanguis::client_messages::visible::visible(
	entity_id const id_,
	bool const visible_)
:
	id_(id_),
	visible_(visible_)
{}

sanguis::entity_id
sanguis::client_messages::visible::id() const
{
	return id_;
}

bool
sanguis::client_messages::visible::get() const
{
	return visible_;
}
