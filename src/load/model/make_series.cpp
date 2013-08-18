#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/model/calc_rect.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_delay.hpp>
#include <sanguis/load/model/make_series.hpp>
#include <sanguis/load/resource/animation/entity.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/box/output.hpp>


sanguis::load::resource::animation::series
sanguis::load::model::make_series(
	sge::parse::json::object const &_json_object,
	sanguis::load::model::global_parameters const &_parameters,
	sge::texture::part const &_texture
)
{
	sge::renderer::lock_rect const area(
		_texture.area()
	);

	sanguis::load::resource::animation::series series;

	// range must be specified
	sge::parse::json::element_vector const &range(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			_json_object.members,
			FCPPT_TEXT("range")
		).elements
	);

	if(
		range.size() < 2
	)
		throw sanguis::exception(
			FCPPT_TEXT("range has too few elements in ")
			+
			fcppt::filesystem::path_to_string(
				_parameters.path()
			)
		);

	sge::renderer::size_type const
		begin(
			sge::parse::json::convert::to_int<
				sge::renderer::size_type
			>(
				range[0]
			)
		),
		end(
			sge::parse::json::convert::to_int<
				sge::renderer::size_type
			>(
				range[1]
			)
		);

	if(
		begin >= end
	)
		throw sanguis::exception(
			FCPPT_TEXT("begin/end invalid: begin = ")
			+
			fcppt::insert_to_fcppt_string(
				begin
			)
			+
			FCPPT_TEXT(", end = ")
			+
			fcppt::insert_to_fcppt_string(
				end
			)
			+
			FCPPT_TEXT(" in ")
			+
			fcppt::filesystem::path_to_string(
				_parameters.path()
			)
		);

	sanguis::duration const delay(
		sanguis::load::model::make_delay(
			_json_object,
			_parameters.delay()
		)
	);

	for(
		sge::renderer::size_type index = begin;
		index != end;
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
					begin
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
