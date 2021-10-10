#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_SENTRY_HPP_INCLUDED

#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>

namespace sanguis::server::weapons::factory
{

sanguis::server::weapons::unique_ptr sentry(sanguis::server::weapons::factory::parameters const &);

}

#endif
