#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_HPP_INCLUDED

#include "scale_fwd.hpp"
#include "scale_type.hpp"
#include "../key_scale.hpp"

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
		actions::scale_type::type,
		control::key_scale
	);

	actions::scale_type::type
	type() const;

	control::key_scale
	get() const;
private:
	actions::scale_type::type type_;

	control::key_scale scale_;
};

}
}
}
}

#endif
