#ifndef SANGUIS_CLIENT_OBJECT_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/object_base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{

using
object_base_unique_ptr
=
fcppt::unique_ptr<
	sanguis::client::object_base
>;

}
}

#endif
