#ifndef SANGUIS_TILES_IMPL_GET_CONTENT_FUNCTION_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_GET_CONTENT_FUNCTION_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/tiles/impl/optional_content_path.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

typedef
fcppt::function<
	sanguis::tiles::impl::optional_content_path (
		sanguis::creator::pos
	)
>
get_content_function;

}
}
}

#endif
