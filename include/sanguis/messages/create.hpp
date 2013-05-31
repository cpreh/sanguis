#ifndef SANGUIS_MESSAGES_CREATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CREATE_HPP_INCLUDED

#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/messages/types/alda_type.hpp>
#include <alda/message/make_concrete_ptr.hpp>


namespace sanguis
{
namespace messages
{

template<
	typename T
>
sanguis::messages::unique_ptr
create(
	T const &_value
)
{
	return
		alda::message::make_concrete_ptr<
			sanguis::messages::types::alda_type
		>(
			_value
		);
}

}
}

#endif
