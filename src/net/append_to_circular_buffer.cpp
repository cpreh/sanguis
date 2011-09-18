#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/circular_buffer_space_left.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>

bool
sanguis::net::append_to_circular_buffer(
	net::circular_buffer &_dest,
	net::data_buffer const &_src
)
{
	if(
		net::circular_buffer_space_left(
			_dest
		)
		< _src.size()
	)
		return false;

	fcppt::algorithm::append(
		_dest,
		_src
	);

	return true;
}
