#include <sanguis/net/data_buffer.hpp>
#include <sanguis/net/data_streambuf.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/iterator/make_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


sanguis::net::data_streambuf::data_streambuf(
	fcppt::reference<
		sanguis::net::data_buffer
	> const _buffer
)
:
	std::streambuf(),
	buffer_(
		_buffer
	)
{
}

sanguis::net::data_streambuf::~data_streambuf()
= default;

std::streamsize
sanguis::net::data_streambuf::xsputn(
	char_type const *const _dest,
	std::streamsize const _size
)
{
	this->buffer_.get() =
		fcppt::container::join(
			std::move(
				this->buffer_.get()
			),
			fcppt::iterator::make_range(
				_dest,
				_dest
				+ // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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
	{
		buffer_.get().push_back(
			traits_type::to_char_type(
				_value
			)
		);
	}

	return
		0;
}
