#include "append_to_circular_buffer.hpp"
#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>

bool
sanguis::net::append_to_circular_buffer(
	net::circular_buffer &_out,
	net::data_buffer const &_in
)
{
	if(
		_out.capacity()
		- _out.size()
		<
		_in.size()
	)
		return false;

	fcppt::algorithm::append(
		_out,
		_in
	);

	return true;
}
