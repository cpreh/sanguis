#ifndef SANGUIS_CLIENT_CONTROL_OPTIONAL_ATTACK_DEST_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_OPTIONAL_ATTACK_DEST_FWD_HPP_INCLUDED

#include <sanguis/client/control/attack_dest_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

typedef
fcppt::optional::object<
	sanguis::client::control::attack_dest
>
optional_attack_dest;

}
}
}

#endif
