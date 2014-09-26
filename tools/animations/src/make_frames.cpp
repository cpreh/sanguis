#include <sanguis/model/animation.hpp>
#include <sanguis/model/cell_area.hpp>
#include <sanguis/model/image_size.hpp>
#include <sanguis/model/make_cell_areas.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/frame.hpp>
#include <sanguis/tools/animations/frame_container.hpp>
#include <sanguis/tools/animations/make_frames.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <QWidget>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::frame_container
sanguis::tools::animations::make_frames(
	QImage const &_image,
	QWidget &_parent,
	sanguis::model::object const &_model,
	sanguis::model::animation const &_animation
)
{
	return
		fcppt::algorithm::map<
			sanguis::tools::animations::frame_container
		>(
			sanguis::model::make_cell_areas(
				sanguis::model::image_size(
					sanguis::model::image_size::value_type(
						fcppt::cast::to_unsigned(
							_image.width()
						),
						fcppt::cast::to_unsigned(
							_image.height()
						)
					)
				),
				_model.cell_size(),
				_animation.animation_range()
			),
			[
				&_parent,
				&_image
			](
				sanguis::model::cell_area const &_area
			)
			{
				return
					sanguis::tools::animations::frame(
						_parent,
						_image,
						_area
					);
			}
		);
}
