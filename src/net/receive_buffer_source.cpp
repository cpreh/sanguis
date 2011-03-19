#include "receive_buffer_source.hpp"
#include "receive_buffer.hpp"
#include <fcppt/algorithm/copy_n.hpp>
#include <algorithm>

sanguis::net::receive_buffer_source::receive_buffer_source(
	net::receive_buffer &_container
)
:
	container_(_container)
{
}

std::streamsize
sanguis::net::receive_buffer_source::read(
	char *const _dest,
	std::streamsize const _count
)
{
	net::receive_buffer::joined_range const range(
		container_.range()
	);

	std::streamsize const real_count(
		std::min(
			static_cast<
				std::streamsize
			>(
				range.size()
			),
			_count
		)
	);

	if(
		real_count == 0
	)
		return -1;

	fcppt::algorithm::copy_n(
		range.begin(),
		real_count,
		_dest
	);

	return real_count;
}
