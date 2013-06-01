#ifndef SANGUIS_MESSAGES_VECTOR2_HPP_INCLUDED
#define SANGUIS_MESSAGES_VECTOR2_HPP_INCLUDED

#include <sanguis/messages/space_unit.hpp>
#include <sanguis/messages/types/vector2.hpp>
#include <alda/bindings/static.hpp>


namespace sanguis
{
namespace messages
{

typedef alda::bindings::static_<
	sanguis::messages::types::vector2,
	sanguis::messages::space_unit
> vector2;

}
}

#endif
