#ifndef SANGUIS_SERVER_ENTITIES_SIMPLE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SIMPLE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/simple_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::entities
{

using
simple_unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::entities::simple
>;

}

#endif
