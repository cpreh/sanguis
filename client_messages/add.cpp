#include "add.hpp"

sanguis::client_messages::add::add(
	const entity_id id_,
	const client_entity_type::type type_)
: id_(id_),
  type_(type_)
{}

sanguis::entity_id
sanguis::client_messages::add::id() const
{
	return id_;
}

sanguis::client_entity_type::type
sanguis::client_messages::add::type() const
{
	return type_;
}
