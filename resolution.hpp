#ifndef SANGUIS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_RESOLUTION_HPP_INCLUDED

#include <sge/renderer/screen_size.hpp>

namespace sanguis
{

sge::renderer::screen_size const
resolution();

void
resolution(
	sge::renderer::screen_size const &
);

}

#endif
