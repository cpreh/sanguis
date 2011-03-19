#ifndef SANGUIS_NET_RECEIVE_BUFFER_SOURCE_HPP_INCLUDED
#define SANGUIS_NET_RECEIVE_BUFFER_SOURCE_HPP_INCLUDED

#include "receive_buffer_fwd.hpp"
#include "value_type.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/iostreams/concepts.hpp>
#include <ios>

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
	net::value_type char_type;

	struct category
	:
		boost::iostreams::input,
		boost::iostreams::device_tag
	{
	};

	explicit receive_buffer_source(
		net::receive_buffer &
	);

	std::streamsize
	read(
		char *,
		std::streamsize
	);
private:
	net::receive_buffer &container_;
};

}
}

#endif
