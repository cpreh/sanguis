#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_HPP_INCLUDED

#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp>
#include <sanguis/client/control/actions/scale_type.hpp>


namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

class scale
{
public:
	scale(
		sanguis::client::control::actions::scale_type,
		sanguis::client::control::key_scale
	);

	sanguis::client::control::actions::scale_type
	type() const;

	sanguis::client::control::key_scale
	get() const;
private:
	sanguis::client::control::actions::scale_type type_;

	sanguis::client::control::key_scale scale_;
};

}
}
}
}

#endif
