#include "message_size.hpp"
#include "message_header_size.hpp"

sanguis::net::size_type
sanguis::net::message_size(
	net::size_type const _body_size
)
{
	return
		_body_size
		+ net::message_header_size;
}
