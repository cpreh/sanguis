#include "receive_buffer_source.hpp"
#include "receive_buffer.hpp"
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/assert/pre.hpp>
#include <algorithm>

sanguis::net::receive_buffer_source::receive_buffer_source(
	net::receive_buffer &_container
)
:
	container_(_container),
	read_count_(0)
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

	read_count_ += real_count;

	return real_count;
}

std::streampos
sanguis::net::receive_buffer_source::seek(
	boost::iostreams::stream_offset const _offset,
	std::ios_base::seekdir const _dir
)
{
	// only here for tellg() to work!
	FCPPT_ASSERT_PRE(
		_offset == 0
	);

	FCPPT_ASSERT_PRE(
		_dir == std::ios_base::cur
	);

	return read_count_;
}
