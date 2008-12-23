#ifndef SANGUIS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_RESOLUTION_HPP_INCLUDED

#include <sge/renderer/screen_types.hpp>

namespace sanguis
{

sge::renderer::screen_size_t const
resolution();

void resolution(
	sge::renderer::screen_size_t const &);

}

#endif
