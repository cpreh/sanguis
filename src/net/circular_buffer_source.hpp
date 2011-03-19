#ifndef SANGUIS_NET_CIRCULAR_BUFFER_SOURCE_HPP_INCLUDED
#define SANGUIS_NET_CIRCULAR_BUFFER_SOURCE_HPP_INCLUDED

#include "circular_buffer.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/iostreams/concepts.hpp>
#include <ios>

namespace sanguis
{
namespace net
{

class circular_buffer_source
{
	FCPPT_NONASSIGNABLE(
		circular_buffer_source
	);
public:
	typedef
	char
	char_type;

	struct category
	:
		boost::iostreams::device_tag
	{
	};

	explicit circular_buffer_source(
		net::circular_buffer &
	);

	std::streamsize
	read(
		char *,
		std::streamsize
	);
private:
	net::circular_buffer &container_;
};

}
}

#endif
