#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_VARIANT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_VARIANT_HPP_INCLUDED

#include <sanguis/client/control/actions/binary.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

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
