#include <sanguis/duration.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_delay.hpp>
#include <sanguis/load/model/make_series.hpp>
#include <sanguis/load/resource/animation/entity.hpp>
#include <sanguis/load/resource/animation/entity_vector.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sanguis/model/animation.hpp>
#include <sanguis/model/cell_area.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/image_size.hpp>
#include <sanguis/model/make_cell_areas.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::load::resource::animation::series
sanguis::load::model::make_series(
	sanguis::model::animation const &_animation,
	sanguis::load::model::global_parameters const &_parameters,
	sge::texture::part const &_texture
)
{
	sge::renderer::lock_rect const area(
		_texture.area()
	);

	sanguis::duration const delay(
		sanguis::load::model::make_delay(
			_animation,
			_parameters.delay()
		)
	);

	return
		sanguis::load::resource::animation::series(
			fcppt::algorithm::map<
				sanguis::load::resource::animation::entity_vector
			>(
				sanguis::model::make_cell_areas(
					sanguis::model::image_size(
						fcppt::math::dim::structure_cast<
							sanguis::model::image_size::value_type
						>(
							area.size()
						)
					),
					sanguis::model::cell_size(
						fcppt::math::dim::structure_cast<
							sanguis::model::cell_size::value_type
						>(
							_parameters.cell_size().get()
						)
					),
					_animation.animation_range()
				),
				[
					area,
					delay,
					&_texture
				](
					sanguis::model::cell_area const &_cell_area
				)
				{
					return
						sanguis::load::resource::animation::entity(
							delay,
							// TODO: Why shared_ptr?
							fcppt::make_shared_ptr<
								sge::texture::part_raw_ref
							>(
								_texture.texture(),
								sge::renderer::lock_rect(
									fcppt::math::vector::structure_cast<
										sge::renderer::lock_rect::vector
									>(
										_cell_area.pos()
									)
									+
									area.pos(),
									fcppt::math::dim::structure_cast<
										sge::renderer::lock_rect::dim
									>(
										_cell_area.size()
									)
								)
							)
						);
				}
			)
		);
}
