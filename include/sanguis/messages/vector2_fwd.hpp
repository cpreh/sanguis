#ifndef SANGUIS_MESSAGES_VECTOR2_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_VECTOR2_FWD_HPP_INCLUDED

#include <sanguis/messages/space_unit_fwd.hpp>
#include <sanguis/messages/types/vector2_fwd.hpp>
#include <alda/bindings/static_fwd.hpp>


namespace sanguis
{
namespace messages
{

typedef
alda::bindings::static_<
	sanguis::messages::types::vector2,
	sanguis::messages::space_unit
>
vector2;

}
}

#endif
