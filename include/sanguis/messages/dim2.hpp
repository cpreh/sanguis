#ifndef SANGUIS_MESSAGES_DIM2_HPP_INCLUDED
#define SANGUIS_MESSAGES_DIM2_HPP_INCLUDED

#include <sanguis/messages/types/dim2.hpp>
#include <sanguis/messages/bindings/static.hpp>
#include <sanguis/messages/size.hpp>

namespace sanguis
{
namespace messages
{

typedef bindings::static_<
	types::dim2,
	messages::size
> dim2;

}
}

#endif
