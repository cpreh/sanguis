#include "loop_method.hpp"
#include "../../../../exception.hpp"
#include <fcppt/text.hpp>

sge::sprite::animation::loop_method::type
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
		return sge::sprite::animation::loop_method::repeat;
	case animation_type::dying:
	case animation_type::deploying:
		return sge::sprite::animation::loop_method::stop_at_end;
	case animation_type::size:
		break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid animation_type in model_part!")
	);
}
