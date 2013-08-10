#include <sanguis/animation_type.hpp>
#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::sprite::animation::loop_method
sanguis::client::draw2d::entities::model::loop_method(
	sanguis::animation_type const _atype
)
{
	switch(
		_atype
	)
	{
	case sanguis::animation_type::none:
	case sanguis::animation_type::walking:
	case sanguis::animation_type::attacking:
	case sanguis::animation_type::reloading:
		return sanguis::client::draw2d::sprite::animation::loop_method::repeat;
	case sanguis::animation_type::dying:
	case sanguis::animation_type::deploying:
		return sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
