#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/const_optional_object_ref.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get_unsigned.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::renderer::lock_rect const
calc_rect(
	sge::renderer::lock_rect const &_area,
	sge::renderer::dim2 const &_cell_size,
	sge::renderer::size_type const _index
)
{
	if(
		_area.size().w() == _cell_size.w()
	)
	{
		FCPPT_ASSERT_ERROR(
			_index == 0u
		);

		return
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector::null(),
				_cell_size
			);
	}

	sge::renderer::dim2 const cell_size_edited(
		_cell_size.w() + 1u,
		_cell_size.h() + 1u
	);

	sge::renderer::size_type const cells_per_row(
		std::max(
			_area.size().w() / cell_size_edited.w(),
			static_cast<
				sge::renderer::size_type
			>(
				1u
			)
		)
	);

	return
		sge::renderer::lock_rect(
			sge::renderer::lock_rect::vector(
				_index % cells_per_row,
				_index / cells_per_row
			) * cell_size_edited + _area.pos(),
			_cell_size
		);
}

sanguis::duration const
load_delay(
	sge::parse::json::member_map const &_members,
	sanguis::load::model::optional_delay const &_opt_delay
)
{
	typedef fcppt::optional<
		int const &
	> optional_int;

	optional_int const ret(
		sge::parse::json::find_member<
			int
		>(
			_members,
			FCPPT_TEXT("delay")
		)
	);

	if(
		ret
	)
		return
			boost::chrono::duration_cast<
				sanguis::duration
			>(
				boost::chrono::milliseconds(
					*ret
				)
			);

	if(
		_opt_delay
	)
		return *_opt_delay;

	throw sanguis::exception(
		FCPPT_TEXT("delay not in header but not in specified in leaf TODO either!")
	);
}

sge::texture::const_part_shared_ptr
load_texture(
	sge::parse::json::object const &_json_object,
	sanguis::load::model::global_parameters const &_param
)
{
	sanguis::load::model::optional_texture_identifier const texture_id(
		_param.new_texture(
			sanguis::load::model::find_texture(
				_json_object.members
			)
		).texture()
	);

	if(
		!texture_id
	)
		throw sanguis::exception(
			FCPPT_TEXT("texture not found in ")
			+ fcppt::filesystem::path_to_string(
				_param.path()
			)
		);

	return
		_param.textures().load(
			_param.path()
			/
			*texture_id
		);
}

sanguis::load::resource::animation::series
load_series(
	sge::parse::json::object const &_json_object,
	sanguis::load::model::global_parameters const &_param,
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
			FCPPT_TEXT("range has too few elements in TODO")
		);

	sge::renderer::size_type const
		begin(
			sge::parse::json::get_unsigned<
				sge::renderer::size_type
			>(
				range[0]
			)
		),
		end(
			sge::parse::json::get_unsigned<
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
			+ fcppt::insert_to_fcppt_string(
				begin
			)
			+ FCPPT_TEXT(", end = ")
			+ fcppt::insert_to_fcppt_string(
				end
			)
			+ FCPPT_TEXT(" in TODO!")
		);

	sanguis::duration const delay(
		::load_delay(
			_json_object.members,
			_param.delay()
		)
	);

	for(
		sge::renderer::size_type index = begin;
		index != end;
		++index
	)
	{
		sge::renderer::lock_rect const cur_area(
			::calc_rect(
				area,
				_param.cell_size(),
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
				FCPPT_TEXT("Rect out of bounds in TODO")
				FCPPT_TEXT(". Whole area of texture is ")
				+ fcppt::insert_to_fcppt_string(
					area
				)
				+ FCPPT_TEXT(" but the inner area is ")
				+ fcppt::insert_to_fcppt_string(
					cur_area
				)
				+ FCPPT_TEXT(". This happened when trying to load index ")
				+ fcppt::insert_to_fcppt_string(
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

}

sanguis::load::model::animation::animation(
	sge::parse::json::object const &_json_object,
	sanguis::load::model::global_parameters const &_param
)
:
	texture_(
		::load_texture(
			_json_object,
			_param
		)
	),
	series_(
		::load_series(
			_json_object,
			_param,
			*texture_
		)
	)
{
}

sanguis::load::model::animation::~animation()
{
}

sanguis::load::resource::animation::series const &
sanguis::load::model::animation::series() const
{
	return series_;
}
