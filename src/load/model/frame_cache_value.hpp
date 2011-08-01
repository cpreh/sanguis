#ifndef SANGUIS_LOAD_MODEL_FRAME_CACHE_VALUE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_FRAME_CACHE_VALUE_HPP_INCLUDED

#include "../../duration.hpp"
#include <sge/renderer/lock_rect.hpp>
#include <fcppt/math/box/basic_decl.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
class frame_cache_value
{
public:
	frame_cache_value(
		sanguis::duration const &,
		sge::renderer::lock_rect const &
	);

	sanguis::duration const &
	delay() const;

	sge::renderer::lock_rect const &
	area() const;
private:
	sanguis::duration delay_;

	sge::renderer::lock_rect area_;
};
}
}
}

#endif
