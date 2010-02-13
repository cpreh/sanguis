#include "animation.hpp"
#include "animation_sound.hpp"
#include "global_parameters.hpp"
#include "find_texture.hpp"
#include "../log.hpp"
#include "../resource/texture_context.hpp"
#include "../resource/textures.hpp"
#include "../resource/texture_context_impl.hpp"
#include "animation_context.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>

namespace
{

sge::renderer::lock_rect const
calc_rect(
	sge::renderer::lock_rect const &area,
	sge::renderer::dim_type const &cell_size,
	sge::renderer::size_type const index)
{
	if (area.dimension().w() == cell_size.w())
	{
		FCPPT_ASSERT(index == static_cast<sge::renderer::size_type>(0));
		return sge::renderer::lock_rect(
			sge::renderer::lock_rect::vector::null(),
			cell_size);
	}

	sge::renderer::dim_type const cell_size_edited(
		cell_size.w()+1,
		cell_size.h()+1);

	sge::renderer::size_type const cells_per_row(
		std::max(
			area.dimension().w() / cell_size_edited.w(),
			static_cast<sge::renderer::size_type>(1)
		)
	);

	return sge::renderer::lock_rect(
		sge::renderer::lock_rect::vector(
			index % cells_per_row,
			index / cells_per_row
		) * cell_size_edited + area.pos(),
		cell_size
	);
}

sge::time::unit
load_delay(
	sge::parse::json::member_vector const &members,
	sanguis::load::model::optional_delay const &opt_delay)
{
	try
	{
		return sge::parse::json::find_member<
			int	
		>(
			members,
			FCPPT_TEXT("delay")
		);
	}
	catch(sge::exception const &)
	{
		if(opt_delay)
			return *opt_delay;
	
		FCPPT_LOG_ERROR(
			sanguis::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("delay not in header but not in specified in leaf TODO")
				<< FCPPT_TEXT(" either!")
		);

		throw;
	}
}

}

sanguis::load::model::animation::animation(
	sge::parse::json::object const &_object,
	global_parameters const &_param)
:
	object_(
		_object),
	param_(
		_param),
	sounds_(),
	texture_()
{
	optional_texture_identifier _texture = 
		param_.new_texture(
			find_texture(
				object_.members
			)
		).texture();

	if(!_texture)
		throw exception(
			FCPPT_TEXT("texture not found in ")
			+ param_.path().string()
		);
	
	texture_ = *_texture;

	try
	{
		sounds_ = fcppt::make_shared_ptr<
			animation_sound
		>(
			sge::parse::json::find_member<
				sge::parse::json::object
			>(
				object_.members,
				FCPPT_TEXT("sounds")
			).members,
			param_.sounds()
		);
	}
	catch(sge::exception const &)
	{
		sounds_ = fcppt::make_shared_ptr<
			animation_sound
		>();
	}

}

sanguis::load::model::animation_sound const &
sanguis::load::model::animation::sounds() const
{
	return *sounds_;
}

sanguis::load::model::animation_context_ptr
sanguis::load::model::animation::load() const 
{
	return 
		animation_context_ptr(
			new animation_context(
				param_.textures().load(
					param_.path() / texture_
				),
				frame_cache_,
				std::tr1::bind(
					&animation::fill_cache,
					this,
					std::tr1::placeholders::_1
				)
			)
		);
}

void sanguis::load::model::animation::fill_cache(
	sge::renderer::lock_rect const &_area) const
{
	if (!frame_cache_.empty())
		return;

	sge::parse::json::element_vector const &range(
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			object_.members,
			FCPPT_TEXT("range")
		).elements
	);

	if(range.size() < 2)
		throw exception(
			FCPPT_TEXT("range has too few elements in TODO")
		);

	sge::renderer::size_type const
		begin(
			sge::parse::json::get<
				int
			>(
				range[0]
			)
		),
		end(
			sge::parse::json::get<
				int	
			>(
				range[1]
			)
		);

	sge::time::unit const delay(
		load_delay(
			object_.members,
			param_.delay()
		)
	);

	for(sge::renderer::size_type i = begin; i != end; ++i)
	{
		sge::renderer::lock_rect const cur_area(
			calc_rect(
				_area,
				param_.cell_size(),
				i
			)
		);

		if(
			!contains(
				_area,
				cur_area
			)
		)
			throw exception(
				FCPPT_TEXT("Rect out of bounds in TODO")
				FCPPT_TEXT(". Whole area of texture is ")
				+ fcppt::lexical_cast<fcppt::string>(_area)
				+ FCPPT_TEXT(" but the inner area is ")
				+ fcppt::lexical_cast<fcppt::string>(cur_area)
				+ FCPPT_TEXT(". This happened when trying to load index ")
				+ fcppt::lexical_cast<fcppt::string>(begin)
			);

		frame_cache_.push_back(
			frame_cache_value(
				delay,
				cur_area
			)
		);
	}
}
