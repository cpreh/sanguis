#ifndef SANGUIS_CLIENT_SYSTEMS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_SYSTEMS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/systems_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

typedef std::unique_ptr<
	sanguis::client::systems
> systems_unique_ptr;

}
}

#endif
