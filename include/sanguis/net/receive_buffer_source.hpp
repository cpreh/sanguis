#ifndef SANGUIS_NET_RECEIVE_BUFFER_SOURCE_HPP_INCLUDED
#define SANGUIS_NET_RECEIVE_BUFFER_SOURCE_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <ios>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

class receive_buffer_source
{
	FCPPT_NONASSIGNABLE(
		receive_buffer_source
	);
public:
	typedef
	alda::net::value_type char_type;

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	struct category
	:
		boost::iostreams::input_seekable,
		boost::iostreams::device_tag
	{
	};

	FCPPT_PP_POP_WARNING

	explicit
	receive_buffer_source(
		alda::net::buffer::circular_receive::object &
	);

	std::streamsize
	read(
		char *,
		std::streamsize
	);

	std::streampos
	seek(
		boost::iostreams::stream_offset,
		std::ios_base::seekdir
	);
private:
	alda::net::buffer::circular_receive::object &container_;

	std::streampos read_count_;
};

}
}

#endif
