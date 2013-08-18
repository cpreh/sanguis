#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sanguis/client/draw2d/center_to_audio_vector.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <fcppt/literal.hpp>


sge::audio::vector const
sanguis::client::draw2d::center_to_audio_vector(
	sanguis::client::draw2d::sprite::center const _center
)
{
	return
		sge::audio::vector(
			static_cast<
				sge::audio::scalar
			>(
				_center.get().x()
			),
			fcppt::literal<
				sge::audio::scalar
			>(
				0
			),
			static_cast<
				sge::audio::scalar
			>(
				_center.get().y()
			)
		);
}
