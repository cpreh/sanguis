#include "receive_buffer_part.hpp"

sanguis::net::receive_buffer_part::receive_buffer_part(
	pointer const _begin,
	pointer const _end
)
:
	begin_(_begin),
	end_(_end)
{
}

sanguis::net::receive_buffer_part::pointer
sanguis::net::receive_buffer_part::begin() const
{
	return begin_;
}

sanguis::net::receive_buffer_part::pointer
sanguis::net::receive_buffer_part::end() const
{
	return end_;
}
