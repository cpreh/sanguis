#include "circular_buffer_source.hpp"
#include <fcppt/algorithm/copy_n.hpp>
#include <algorithm>

sanguis::net::circular_buffer_source::circular_buffer_source(
	net::circular_buffer &_container
)
:
	container_(_container)
{
}

std::streamsize
sanguis::net::circular_buffer_source::read(
	char *const _dest,
	std::streamsize const _count
)
{
	std::streamsize const real_count(
		std::min(
			_count,
			static_cast<
				std::streamsize
			>(
				container_.size()
			)
		)
	);

	if(
		real_count == 0
	)
		return -1;

	fcppt::algorithm::copy_n(
		container_.begin(),
		real_count,
		_dest
	);

	container_.erase(
		container_.begin(),
		container_.begin()
		+ real_count
	);

	return real_count;
}
