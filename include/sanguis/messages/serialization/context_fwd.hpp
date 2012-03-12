#ifndef SANGUIS_MESSAGES_SERIALIZATION_CONTEXT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_CONTEXT_FWD_HPP_INCLUDED

#include <sanguis/messages/types/alda_type.hpp>
#include <alda/serialization/context_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace serialization
{

typedef alda::serialization::context<
	sanguis::messages::types::alda_type
> context;

}
}
}

#endif
