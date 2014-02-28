#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/model/calc_rect.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_delay.hpp>
#include <sanguis/load/model/make_series.hpp>
#include <sanguis/load/resource/animation/entity.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/box/output.hpp>


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

	sanguis::model::animation_range const range(
		_animation.animation_range()
	);

	if(
		range.begin()
		>=
		range.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("begin/end invalid: begin = ")
			+
			fcppt::insert_to_fcppt_string(
				range.begin()
			)
			+
			FCPPT_TEXT(", end = ")
			+
			fcppt::insert_to_fcppt_string(
				range.end()
			)
			+
			FCPPT_TEXT(" in ")
			+
			fcppt::filesystem::path_to_string(
				_parameters.path()
			)
		);

	sanguis::load::resource::animation::series series;

	sanguis::duration const delay(
		sanguis::load::model::make_delay(
			_animation,
			_parameters.delay()
		)
	);

	for(
		sge::renderer::size_type index(
			range.begin()
		);
		index != range.end();
		++index
	)
	{
		sge::renderer::lock_rect const cur_area(
			sanguis::load::model::calc_rect(
				area,
				_parameters.cell_size(),
				index
			)
		);

		if(
			!fcppt::math::box::contains(
				area,
				cur_area
			)
		)
			throw sanguis::exception(
				FCPPT_TEXT("Rect out of bounds in ")
				+
				fcppt::filesystem::path_to_string(
					_parameters.path()
				)
				+
				FCPPT_TEXT(". Whole area of texture is ")
				+
				fcppt::insert_to_fcppt_string(
					area
				)
				+
				FCPPT_TEXT(" but the inner area is ")
				+
				fcppt::insert_to_fcppt_string(
					cur_area
				)
				+
				FCPPT_TEXT(". This happened when trying to load index ")
				+
				fcppt::insert_to_fcppt_string(
					range.begin()
				)
			);

		series.push_back(
			sanguis::load::resource::animation::entity(
				delay,
				sge::texture::const_part_shared_ptr(
					fcppt::make_shared_ptr<
						sge::texture::part_raw_ref
					>(
						_texture.texture(),
						cur_area
					)
				)
			)
		);
	}

	return
		series;
}
