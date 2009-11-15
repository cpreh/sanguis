#ifndef SANGUIS_MESSAGES_MAKE_MESSAGE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_MESSAGE_ID_HPP_INCLUDED

#include "types/message.hpp"
#include "types/message_type.hpp"
#include "roles/type.hpp"
#include "bindings/fundamental.hpp"
#include <majutsu/constant.hpp>
#include <majutsu/role.hpp>

namespace sanguis
{
namespace messages
{

template<
	types::message::type Msg
>
struct make_message_id {
private:
	static types::message_type const
	converted_message =
		static_cast<types::message_type>(Msg);
public:
	typedef majutsu::role<
		majutsu::constant<
			bindings::fundamental<
				types::message_type
			>,
			converted_message
		>,
		roles::type
	> type;
};

}
}

#endif
