#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_NULLARY_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_NULLARY_HPP_INCLUDED

#include <sanguis/client/control/actions/nullary_fwd.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>


namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

class nullary
{
public:
	explicit
	nullary(
		sanguis::client::control::actions::nullary_type
	);

	sanguis::client::control::actions::nullary_type
	type() const;
private:
	sanguis::client::control::actions::nullary_type type_;
};

}
}
}
}

#endif
