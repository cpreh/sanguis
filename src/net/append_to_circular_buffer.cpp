#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <fcppt/algorithm/append.hpp>


bool
sanguis::net::append_to_circular_buffer(
	alda::net::buffer::circular_send::object &_dest,
	sanguis::net::data_buffer const &_src
)
{
	if(
		_dest.space_left()
		<
		_src.size()
	)
		return false;

	fcppt::algorithm::append(
		_dest.get(),
		_src
	);

	return true;
}
