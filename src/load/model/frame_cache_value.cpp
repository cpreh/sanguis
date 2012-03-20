#include <sanguis/load/model/frame_cache_value.hpp>
#include <fcppt/math/box/object_impl.hpp>

sanguis::load::model::frame_cache_value::frame_cache_value(
	sanguis::duration const &_delay,
	sge::renderer::lock_rect const &_area
)
:
	delay_(
		_delay
	),
	area_(
		_area
	)
{
}

sanguis::duration const &
sanguis::load::model::frame_cache_value::delay() const
{
	return delay_;
}

sge::renderer::lock_rect const &
sanguis::load::model::frame_cache_value::area() const
{
	return area_;
}
