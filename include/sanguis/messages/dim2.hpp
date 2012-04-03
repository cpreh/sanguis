#ifndef SANGUIS_MESSAGES_DIM2_HPP_INCLUDED
#define SANGUIS_MESSAGES_DIM2_HPP_INCLUDED

#include <sanguis/messages/types/dim2.hpp>
#include <sanguis/messages/size.hpp>
#include <alda/bindings/static.hpp>

namespace sanguis
{
namespace messages
{

typedef alda::bindings::static_<
	sanguis::messages::types::dim2,
	sanguis::messages::size
> dim2;

}
}

#endif
