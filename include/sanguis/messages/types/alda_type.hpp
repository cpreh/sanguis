#ifndef SANGUIS_MESSAGES_TYPES_ALDA_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_ALDA_TYPE_HPP_INCLUDED

#include <sanguis/messages/types/message.hpp>
#include <alda/type_enum.hpp>


namespace sanguis
{
namespace messages
{
namespace types
{

typedef alda::type_enum<
	sanguis::messages::types::message,
	sanguis::messages::types::message::size
> alda_type;

}
}
}

#endif
