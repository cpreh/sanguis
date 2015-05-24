#ifndef SANGUIS_CLIENT_DRAW_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace draw
{

typedef
fcppt::unique_ptr<
	sanguis::client::draw::base
>
base_unique_ptr;

}
}
}

#endif
