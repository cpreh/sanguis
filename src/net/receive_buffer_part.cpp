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

sanguis::net::receive_buffer_part::size_type
sanguis::net::receive_buffer_part::size() const
{
	return
		static_cast<
			size_type
		>(
			this->end() - this->begin()
		);
}

bool
sanguis::net::receive_buffer_part::empty() const
{
	return
		this->begin() == this->end();
}
