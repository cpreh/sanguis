#ifndef SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/client/control/attack_dest_fwd.hpp>
#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

class environment
{
	FCPPT_NONCOPYABLE(
		environment
	);
protected:
	environment();
public:
	virtual
	sanguis::client::control::attack_dest const
	translate_attack_dest(
		sanguis::client::control::cursor_position const &
	) const = 0;

	virtual
	~environment() = 0;
};

}
}
}

#endif
