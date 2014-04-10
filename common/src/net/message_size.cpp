#include <sanguis/net/message_size.hpp>
#include <sanguis/net/message_header_size.hpp>
#include <alda/net/size_type.hpp>


alda::net::size_type
sanguis::net::message_size(
	alda::net::size_type const _body_size
)
{
	return
		_body_size
		+ sanguis::net::message_header_size::value;
}
