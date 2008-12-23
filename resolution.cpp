#include "resolution.hpp"

namespace
{

sge::renderer::screen_size_t resolution_(
	0, 0);

}

sge::renderer::screen_size_t const
sanguis::resolution()
{
	return resolution_;//sge::renderer::screen_size_t(1024,768);
}

void sanguis::resolution(
	sge::renderer::screen_size_t const &nres)
{
	resolution_ = nres;
}
