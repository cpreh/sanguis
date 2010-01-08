#include "add.hpp"

sanguis::client::messages::add::add(
	entity_id const id_,
	entity_type::type const type_
)
:
	id_(id_),
	type_(type_)
{}

sanguis::entity_id
sanguis::client::messages::add::id() const
{
	return id_;
}

sanguis::client::entity_type::type
sanguis::client::messages::add::type() const
{
	return type_;
}
