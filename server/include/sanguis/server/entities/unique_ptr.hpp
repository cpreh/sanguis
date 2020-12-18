#ifndef SANGUIS_SERVER_ENTITIES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

using
unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::entities::base
>;

}
}
}

#endif
