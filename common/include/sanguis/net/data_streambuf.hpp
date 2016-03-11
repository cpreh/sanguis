#ifndef SANGUIS_NET_DATA_STREAMBUF_HPP_INCLUDED
#define SANGUIS_NET_DATA_STREAMBUF_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/net/data_buffer_fwd.hpp>
#include <sanguis/net/data_streambuf_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

class data_streambuf
:
	public std::streambuf
{
	FCPPT_NONCOPYABLE(
		data_streambuf
	);
public:
	SANGUIS_COMMON_SYMBOL
	explicit
	data_streambuf(
		sanguis::net::data_buffer &
	);

	SANGUIS_COMMON_SYMBOL
	~data_streambuf()
	override;
private:
	std::streamsize
	xsputn(
		char_type const *,
		std::streamsize
	)
	override;

	int_type
	overflow(
		int_type
	)
	override;

	sanguis::net::data_buffer &buffer_;
};

}
}

#endif
