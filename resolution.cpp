#include "resolution.hpp"
#include <sge/math/dim/basic_impl.hpp>

namespace
{

sge::renderer::screen_size_t resolution_(
	0, 0);

}

sge::renderer::screen_size_t const
sanguis::resolution()
{
	return resolution_;
}

void sanguis::resolution(
	sge::renderer::screen_size_t const &nres)
{
	resolution_ = nres;
}
