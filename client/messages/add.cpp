#include "add.hpp"

sanguis::client::messages::add::add(
	entity_type::type const type_
)
:
	type_(type_)
{}

sanguis::client::entity_type::type
sanguis::client::messages::add::type() const
{
	return type_;
}
