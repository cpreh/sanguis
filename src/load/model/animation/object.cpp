#include <sanguis/load/model/animation/object.hpp>
#include <sanguis/load/model/animation/context.hpp>
#include <sanguis/load/model/animation/sound.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/resource/texture_context.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/texture_context_impl.hpp>
#include <sanguis/exception.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/parse/json/get_unsigned.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/texture/part_raw.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

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
			_index == static_cast<sge::renderer::size_type>(0)
		);

		return
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector::null(),
				_cell_size
			);
	}

	sge::renderer::dim2 const cell_size_edited(
		_cell_size.w() + 1,
		_cell_size.h() + 1
	);

	sge::renderer::size_type const cells_per_row(
		std::max(
			_area.size().w() / cell_size_edited.w(),
			static_cast<sge::renderer::size_type>(1)
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
	sge::parse::json::member_vector const &_members,
	sanguis::load::model::optional_delay const &_opt_delay
)
{
	int const *const ret(
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
			fcppt::chrono::duration_cast<
				sanguis::duration
			>(
				fcppt::chrono::milliseconds(
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

}

sanguis::load::model::animation::object::~object()
{
}

sanguis::load::model::animation::object::object(
	sge::parse::json::object const &_object,
	global_parameters const &_param
)
:
	object_(
		_object
	),
	param_(
		_param
	),
	sounds_(),
	texture_()
{
	optional_texture_identifier _texture =
		param_.new_texture(
			find_texture(
				object_.members
			)
		).texture();

	if(
		!_texture
	)
		throw sanguis::exception(
			FCPPT_TEXT("texture not found in ")
			+ fcppt::filesystem::path_to_string(
				param_.path()
			)
		);

	texture_ = *_texture;

	{
		sge::parse::json::object const *const sounds_object(
			sge::parse::json::find_member<
				sge::parse::json::object
			>(
				object_.members,
				FCPPT_TEXT("sounds")
			)
		);

		if(
			sounds_object
		)
			sounds_.take(
				fcppt::make_unique_ptr<
					model::animation::sound
				>(
					sounds_object->members,
					fcppt::cref(
						param_.sounds()
					)
				)
			);
		else
			sounds_.take(
				fcppt::make_unique_ptr<
					animation::sound
				>()
			);
	}
}

sanguis::load::model::animation::sound const &
sanguis::load::model::animation::object::sounds() const
{
	return *sounds_;
}

sanguis::load::model::animation::context_ptr
sanguis::load::model::animation::object::load() const
{
	return
		// TODO: make_unique_ptr?
		animation::context_ptr(
			new animation::context(
				param_.textures().load(
					param_.path() / texture_
				),
				frame_cache_,
				std::tr1::bind(
					&object::fill_cache,
					this,
					std::tr1::placeholders::_1
				)
			)
		);
}

void
sanguis::load::model::animation::object::fill_cache(
	sge::renderer::lock_rect const &_area
) const
{
	if(
		!frame_cache_.empty()
	)
		return;

	// range must be specified
	sge::parse::json::element_vector const &range(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			object_.members,
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
			+ fcppt::lexical_cast<fcppt::string>(begin)
			+ FCPPT_TEXT(", end = ")
			+ fcppt::lexical_cast<fcppt::string>(end)
			+ FCPPT_TEXT(" in TODO!")
		);

	sanguis::duration const delay(
		::load_delay(
			object_.members,
			param_.delay()
		)
	);

	for(
		sge::renderer::size_type index = begin;
		index != end;
		++index
	)
	{
		sge::renderer::lock_rect const cur_area(
			calc_rect(
				_area,
				param_.cell_size(),
				index
			)
		);

		if(
			!fcppt::math::box::contains(
				_area,
				cur_area
			)
		)
			throw sanguis::exception(
				FCPPT_TEXT("Rect out of bounds in TODO")
				FCPPT_TEXT(". Whole area of texture is ")
				+ fcppt::lexical_cast<fcppt::string>(_area)
				+ FCPPT_TEXT(" but the inner area is ")
				+ fcppt::lexical_cast<fcppt::string>(cur_area)
				+ FCPPT_TEXT(". This happened when trying to load index ")
				+ fcppt::lexical_cast<fcppt::string>(begin)
			);

		frame_cache_.push_back(
			model::frame_cache_value(
				delay,
				cur_area
			)
		);
	}
}
