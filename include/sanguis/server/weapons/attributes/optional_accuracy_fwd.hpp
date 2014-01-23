#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_OPTIONAL_ACCURACY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_OPTIONAL_ACCURACY_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/attributes/accuracy_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace attributes
{

typedef
fcppt::optional<
	sanguis::server::weapons::attributes::accuracy
>
optional_accuracy;

}
}
}
}

#endif
