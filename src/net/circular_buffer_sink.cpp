#include <sanguis/net/circular_buffer_sink.hpp>
#include <sanguis/net/circular_buffer_space_left.hpp>

sanguis::net::circular_buffer_sink::circular_buffer_sink(
	net::circular_buffer &_container
)
:
	container_(_container)
{
}

std::streamsize
sanguis::net::circular_buffer_sink::write(
	char const *const _data,
	std::streamsize const _size
)
{
	// write nothing if there is not enough space
	if(
		static_cast<
			std::streamsize
		>(
			net::circular_buffer_space_left(
				container_
			)
		)
		< _size
	)
		return -1;

	container_.insert(
		container_.end(),
		_data,
		_data + _size
	);

	return _size;
}
