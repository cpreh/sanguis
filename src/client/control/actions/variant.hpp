#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_VARIANT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_VARIANT_HPP_INCLUDED

#include "binary.hpp"
#include "cursor.hpp"
#include "nullary.hpp"
#include "scale.hpp"
#include <fcppt/variant/object.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

typedef fcppt::variant::object<
	boost::mpl::vector4<
		actions::binary,
		actions::cursor,
		actions::nullary,
		actions::scale
	>
> variant;

}
}
}
}

#endif
