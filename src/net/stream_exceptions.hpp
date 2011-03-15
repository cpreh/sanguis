#ifndef SANGUIS_NET_STREAM_EXCEPTIONS_HPP_INCLUDED
#define SANGUIS_NET_STREAM_EXCEPTIONS_HPP_INCLUDED

#include <ios>

namespace sanguis
{
namespace net
{

template<
	typename Stream
>
void
stream_exceptions(
	Stream &_stream
)
{
	_stream.exceptions(
		std::ios_base::badbit
		| std::ios_base::failbit
		| std::ios_base::eofbit
	);
}

}
}

#endif
