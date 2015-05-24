#ifndef SANGUIS_SERVER_OBJECT_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/object_base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::unique_ptr<
	sanguis::server::object_base
>
object_base_unique_ptr;

}
}

#endif
