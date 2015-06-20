#ifndef SANGUIS_MESSAGES_CLIENT_CREATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CREATE_HPP_INCLUDED

#include <sanguis/messages/client/concrete.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

template<
	typename T
>
inline
sanguis::messages::client::concrete<
	T
>
create(
	T const &_value
)
{
	return
		sanguis::messages::client::concrete<
			T
		>(
			_value
		);
}

}
}
}

#endif
