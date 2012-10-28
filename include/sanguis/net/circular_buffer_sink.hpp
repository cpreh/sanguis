#ifndef SANGUIS_NET_CIRCULAR_BUFFER_SINK_HPP_INCLUDED
#define SANGUIS_NET_CIRCULAR_BUFFER_SINK_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

class circular_buffer_sink
{
	FCPPT_NONASSIGNABLE(
		circular_buffer_sink
	);
public:
	typedef alda::net::value_type
	char_type;

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	struct category
	:
		boost::iostreams::output,
		boost::iostreams::device_tag
	{
	};

	FCPPT_PP_POP_WARNING

	explicit
	circular_buffer_sink(
		alda::net::buffer::circular_send::object &
	);

	std::streamsize
	write(
		char const *,
		std::streamsize
	);
private:
	alda::net::buffer::circular_send::object &container_;
};

}
}

#endif
