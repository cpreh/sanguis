#ifndef SANGUIS_SERVER_ENTITIES_SIMPLE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SIMPLE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/simple_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::unique_ptr<
	sanguis::server::entities::simple
>
simple_unique_ptr;

}
}
}

#endif
