#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <fcppt/assert/unreachable.hpp>

sanguis::client::draw2d::sprite::animation::loop_method::type
sanguis::client::draw2d::entities::model::loop_method(
	animation_type::type const _atype
)
{
	switch(
		_atype
	)
	{
	case animation_type::none:
	case animation_type::walking:
	case animation_type::attacking:
	case animation_type::reloading:
		return sanguis::client::draw2d::sprite::animation::loop_method::repeat;
	case animation_type::dying:
	case animation_type::deploying:
		return sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end;
	case animation_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
