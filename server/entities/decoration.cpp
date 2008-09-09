#include "decoration.hpp"
#include "../message_converter.hpp"

sanguis::server::entities::decoration::decoration(base_parameters const &b,decoration_type::type const type_)
	: entity(b),
	  type_(type_)
{
}

sanguis::decoration_type::type sanguis::server::entities::decoration::type() const
{
	return type_;
}

sanguis::messages::auto_ptr sanguis::server::entities::decoration::add_message() const
{
	return message_convert(*this);
}
