#ifndef SANGUIS_LOAD_MODEL_FRAME_CACHE_VALUE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_FRAME_CACHE_VALUE_HPP_INCLUDED

#include <sge/time/unit.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/math/box/basic_decl.hpp>

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
		sge::time::unit,
		sge::renderer::lock_rect const &);
	sge::time::unit delay() const;
	sge::renderer::lock_rect const &area() const;
private:
	sge::time::unit delay_;
	sge::renderer::lock_rect area_;
};
}
}
}

#endif
