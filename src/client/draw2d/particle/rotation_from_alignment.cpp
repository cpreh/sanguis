#include <sanguis/random_generator.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/particle/rotation_from_alignment.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_real_impl.hpp>


sanguis::client::draw2d::particle::rotation const
sanguis::client::draw2d::particle::rotation_from_alignment(
	particle::align_type::type const _alignment,
	draw2d::center const &_refpoint,
	particle::uniform_rotation &_rot_angle
)
{
	switch(
		_alignment
	)
	{
	case align_type::none:
		return
			particle::rotation(
				0.f
			);
	case align_type::to_center:
		return
			fcppt::math::vector::length(
				_refpoint.get()
			)
			<
			static_cast<
				draw2d::funit
			>(
				0.0001f
			)
			?
				particle::rotation(
					0.f
				)
			:
				particle::rotation(
					fcppt::math::vector::signed_angle_between_cast<
						particle::rotation::value_type
					>(
						draw2d::center::value_type::null(),
						_refpoint.get()
					)
				);
	case align_type::random:
		return
			particle::rotation(
				_rot_angle()
			);
	case align_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
