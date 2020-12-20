#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_REF_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_REF_HPP_INCLUDED

#include <sanguis/client/config/settings/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

using
object_ref
=
fcppt::reference<
	sanguis::client::config::settings::object
>;

}
}
}
}

#endif
