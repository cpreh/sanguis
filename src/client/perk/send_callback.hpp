#ifndef SANGUIS_CLIENT_PERK_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_SEND_CALLBACK_HPP_INCLUDED

#include "../../perk_type.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef fcppt::function::object<
	void (perk_type::type)
> send_callback;

}
}
}

#endif
