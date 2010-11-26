#include "rotation_from_alignment.hpp"
#include "../../../exception.hpp"
#include <fcppt/math/vector/signed_angle_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/random/uniform_impl.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::rotation
sanguis::client::draw2d::particle::rotation_from_alignment(
	align_type::type const _alignment,
	point const &_refpoint,
	uniform_rotation &_rot_angle
)
{
	switch (_alignment)
	{
		case align_type::none:
			return  static_cast<rotation>(0);
		case align_type::to_center:
			return
				fcppt::math::vector::is_null(
					_refpoint
				)
				?
					static_cast<rotation>(0)
				:
					fcppt::math::vector::signed_angle_cast<
						rotation
					>(
						point::null(),
						_refpoint
					);
		case align_type::random:
			return _rot_angle();
		case align_type::size:
			break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("invalid align type")
	);
}
