#ifndef SANGUIS_NET_CIRCULAR_BUFFER_SINK_HPP_INCLUDED
#define SANGUIS_NET_CIRCULAR_BUFFER_SINK_HPP_INCLUDED

#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/value_type.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <ios>
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
	typedef net::value_type
	char_type;

	struct category
	:
		boost::iostreams::output,
		boost::iostreams::device_tag
	{
	};

	explicit circular_buffer_sink(
		net::circular_buffer &
	);

	std::streamsize
	write(
		char const *,
		std::streamsize
	);
private:
	net::circular_buffer &container_;
};

}
}

#endif
