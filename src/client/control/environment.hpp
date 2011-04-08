#ifndef SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "attack_dest.hpp"
#include "cursor_position.hpp"
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
	virtual control::attack_dest const 
	translate_attack_dest(
		control::cursor_position const &	
	) const = 0;

	virtual ~environment();
};

}
}
}

#endif
