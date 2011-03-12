#ifndef SANGUIS_MESSAGES_MESSAGE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_MESSAGE_ID_HPP_INCLUDED

#include "roles/type.hpp"
#include <majutsu/extract_constant.hpp>

namespace sanguis
{
namespace messages
{

template<
	typename Message
>
struct message_id
:
majutsu::extract_constant<
	Message,
	roles::type
>
{};

}
}

#endif
