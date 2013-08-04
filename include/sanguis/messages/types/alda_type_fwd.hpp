#ifndef SANGUIS_MESSAGES_TYPES_ALDA_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_ALDA_TYPE_FWD_HPP_INCLUDED

#include <sanguis/messages/types/message.hpp>
#include <alda/type_enum_fcppt_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace types
{

typedef alda::type_enum_fcppt<
	sanguis::messages::types::message
> alda_type;

}
}
}

#endif
