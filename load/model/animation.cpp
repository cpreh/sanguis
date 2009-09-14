#include "animation.hpp"
#include "../resource/texture_context.hpp"
#include "animation_sound.hpp"
#include "global_parameters.hpp"
#include "find_texture.hpp"
#include "../resource/textures.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "../resource/texture_context_impl.hpp"
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/rect/output.hpp>
#include <sge/math/rect/contains.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/log/headers.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <sge/lexical_cast.hpp>
#include <boost/foreach.hpp>

namespace
{

sge::renderer::lock_rect const
calc_rect(
	sge::renderer::lock_rect const &area,
	sge::renderer::dim_type const &cell_size,
	sge::renderer::size_type const index)
{
	if (area.dim().w() == cell_size.w())
	{
		SGE_ASSERT(index == static_cast<sge::renderer::size_type>(0));
		return sge::renderer::lock_rect(
			sge::renderer::lock_rect::point_type::null(),
			cell_size);
	}

	sge::renderer::dim_type const cell_size_edited(
		cell_size.w()+1,
		cell_size.h()+1);

	sge::renderer::size_type const cells_per_row(
		std::max(
			area.dim().w() / cell_size_edited.w(),
			static_cast<sge::renderer::size_type>(1)
		)
	);

	return sge::renderer::lock_rect(
		sge::renderer::lock_rect::point_type(
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
			SGE_TEXT("delay")
		);
	}
	catch(sge::exception const &)
	{
		if(opt_delay)
			return *opt_delay;
	
		SGE_LOG_ERROR(
			sanguis::load::log(),
			sge::log::_1
				<< SGE_TEXT("delay not in header but not in specified in leaf TODO")
				<< SGE_TEXT(" either!")
		);

		throw;
	}
}

}

sanguis::load::model::animation::animation(
	sge::parse::json::object const &object,
	global_parameters const &_param)
:
	param_(
		_param),
	members_(
		object.members),
	context_(),
	anim(),
	sounds_()
{
	try
	{
		sounds_ = sge::make_shared_ptr<
			animation_sound
		>(
			sge::parse::json::find_member<
				sge::parse::json::object
			>(
				members_,
				SGE_TEXT("sounds")
			).members,
			param_.sounds()
		);
	}
	catch(sge::exception const &)
	{
		sounds_ = sge::make_shared_ptr<
			animation_sound
		>();
	}

	optional_texture_identifier const texture(
		param_.new_texture(
			find_texture(
				members_
			)
		).texture()
	);
	
	if(!texture)
		throw exception(
			SGE_TEXT("texture not found in ")
			+ param_.path().string()
		);

	sge::cerr << "creating texture context for animation\n";
	context_ = 
		param_.textures().load(
			param_.path() / *texture);
	//update(); // DEBUG
}

sge::sprite::animation_series const &
sanguis::load::model::animation::get() const
{
	return *anim;
}

sanguis::load::model::animation_sound const &
sanguis::load::model::animation::sounds() const
{
	return *sounds_;
}

bool sanguis::load::model::animation::update() const
{
	if (anim)
		return true;
	if (!context_.value()->update())
		return false;
	
	anim.reset(
		new sge::sprite::animation_series());

	// TODO: let the context return sge::image::file_ptr instead and convert to part_ptr here
	sge::texture::part_ptr const tex = 
		context_.value()->result();

	sge::parse::json::element_vector const &range(
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			members_,
			SGE_TEXT("range")
		).elements
	);

	if(range.size() < 2)
		throw exception(
			SGE_TEXT("range has too few elements in TODO")
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
			members_,
			param_.delay()
		)
	);
	sge::renderer::lock_rect const area(
		tex->area()
	);

	for(sge::renderer::size_type i = begin; i != end; ++i)
	{
		sge::renderer::lock_rect const cur_area(
			calc_rect(
				area,
				param_.cell_size(),
				i
			)
		);

		if(
			!contains(
				area,
				cur_area
			)
		)
			throw exception(
				SGE_TEXT("Rect out of bounds in TODO")
				SGE_TEXT(". Whole area of texture is ")
				+ sge::lexical_cast<sge::string>(area	)
				+ SGE_TEXT(" but the inner area is ")
				+ sge::lexical_cast<sge::string>(cur_area)
				+ SGE_TEXT(". This happened when trying to load index ")
				+ sge::lexical_cast<sge::string>(begin)
			);

		anim->push_back(
			sge::sprite::animation_entity(
				sge::time::millisecond(
					delay
				),
				sge::texture::const_part_ptr(
					sge::make_shared_ptr<
						sge::texture::part_raw
					>(
						tex->texture(),
						cur_area
					)
				)
			)
		);
	}
	return true;
}
