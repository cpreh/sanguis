#include <sanguis/net/data_buffer.hpp>
#include <sanguis/net/data_streambuf.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <ios>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


sanguis::net::data_streambuf::data_streambuf(
	sanguis::net::data_buffer &_buffer
)
:
	std::streambuf(),
	buffer_(
		_buffer
	)
{
}

sanguis::net::data_streambuf::~data_streambuf()
{
}

std::streamsize
sanguis::net::data_streambuf::xsputn(
	char_type const *const _dest,
	std::streamsize const _size
)
{
	fcppt::algorithm::append(
		buffer_,
		boost::make_iterator_range(
			_dest,
			_dest
			+
			_size
		)
	);

	return
		_size;
}

sanguis::net::data_streambuf::int_type
sanguis::net::data_streambuf::overflow(
	int_type const _value
)
{
	if(
		!traits_type::eq_int_type(
			_value,
			traits_type::eof()
		)
	)
		buffer_.push_back(
			traits_type::to_char_type(
				_value
			)
		);

	return
		0;
}
