#include "resolution.hpp"
#include <sge/math/dim/basic_impl.hpp>

namespace
{

sge::renderer::screen_size resolution_(
	sge::renderer::screen_size::null()
);

}

sge::renderer::screen_size const
sanguis::resolution()
{
	return resolution_;
}

void sanguis::resolution(
	sge::renderer::screen_size const &nres)
{
	resolution_ = nres;
}
