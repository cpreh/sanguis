#ifndef SANGUIS_NET_DETAIL_EXCEPTIONS_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_EXCEPTIONS_HPP_INCLUDED

#include <ios>

namespace sanguis
{
namespace net
{
namespace detail
{

template<
	typename Stream
>
void
exceptions(
	Stream &stream
)
{
	stream.exceptions(
		std::ios_base::badbit
		| std::ios_base::failbit
		| std::ios_base::eofbit
	);
}

}
}
}

#endif
