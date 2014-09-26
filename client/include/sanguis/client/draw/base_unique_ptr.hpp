#ifndef SANGUIS_CLIENT_DRAW_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw
{

typedef
std::unique_ptr<
	sanguis::client::draw::base
>
base_unique_ptr;

}
}
}

#endif
