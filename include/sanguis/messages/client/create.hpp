#ifndef SANGUIS_MESSAGES_CLIENT_CREATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CREATE_HPP_INCLUDED

#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/message/make_concrete_ptr.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

template<
	typename T
>
sanguis::messages::client::unique_ptr
create(
	T const &_value
)
{
	// TODO: Can we remove this?
	return
		alda::message::make_concrete_ptr<
			sanguis::messages::client::types::alda_type
		>(
			_value
		);
}

}
}
}

#endif
