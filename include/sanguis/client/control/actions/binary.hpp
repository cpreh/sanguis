#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_BINARY_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_BINARY_HPP_INCLUDED

#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/binary_type.hpp>


namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

class binary
{
public:
	binary(
		sanguis::client::control::actions::binary_type,
		bool
	);

	sanguis::client::control::actions::binary_type
	type() const;

	bool
	value() const;
private:
	sanguis::client::control::actions::binary_type type_;

	bool value_;
};

}
}
}
}

#endif
