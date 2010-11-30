#include "add.hpp"

sanguis::client::messages::add::add(
	entity_type::type const _type
)
:
	type_(_type)
{}

sanguis::client::entity_type::type
sanguis::client::messages::add::type() const
{
	return type_;
}
