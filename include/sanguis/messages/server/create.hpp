#ifndef SANGUIS_MESSAGES_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CREATE_HPP_INCLUDED

#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/message/make_concrete_ptr.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

template<
	typename T
>
sanguis::messages::server::unique_ptr
create(
	T const &_value
)
{
	// TODO: Can we remove this?
	return
		alda::message::make_concrete_ptr<
			sanguis::messages::server::types::alda_type
		>(
			_value
		);
}

}
}
}

#endif
