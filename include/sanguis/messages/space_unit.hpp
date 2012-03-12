#ifndef SANGUIS_MESSAGES_SPACE_UNIT_HPP_INCLUDED
#define SANGUIS_MESSAGES_SPACE_UNIT_HPP_INCLUDED

#include <sanguis/messages/types/space_unit.hpp>
#include <alda/bindings/fundamental.hpp>

namespace sanguis
{
namespace messages
{

typedef alda::bindings::fundamental<
	sanguis::messages::types::space_unit
> space_unit;

}
}

#endif
