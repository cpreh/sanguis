#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_ANY_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_ANY_HPP_INCLUDED

#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/control/actions/variant.hpp>

namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

class any
{
public:
	explicit any(
		actions::variant const &
	);

	actions::variant const &
	get() const;
private:
	actions::variant variant_;
};

}
}
}
}

#endif
