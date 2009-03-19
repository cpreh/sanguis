#include "animation.hpp"
#include "get_entry.hpp"
#include "animation_sound.hpp"
#include "global_parameters.hpp"
#include "../resource/animations.hpp"
#include "../resource/context.hpp"
#include "../log.hpp"
#include <sge/parse/ini/entry.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

namespace
{

sge::renderer::lock_rect const
calc_rect(
	sge::renderer::lock_rect const &area,
	sge::renderer::dim_type const &cell_size,
	sge::renderer::size_type const index)
{
	sge::renderer::size_type const cells_per_row(
		area.dim().w() / cell_size.w() 
	);

	return sge::renderer::lock_rect(
		sge::renderer::lock_rect::point_type(
			index % cells_per_row,
			index / cells_per_row
		) * cell_size + area.pos(),
		cell_size
	);
}

sge::time::unit
load_delay(
	sge::parse::ini::entry_vector const &entries,
	sanguis::load::model::optional_delay const &opt_delay,
	sge::filesystem::path const &path)
{
	if(opt_delay)
		return *opt_delay;
	
	try
	{
		return sanguis::load::model::get_entry<
			int	
		>(
			entries,
			SGE_TEXT("delay")
		);
	}
	catch(sanguis::exception const &)
	{
		SGE_LOG_ERROR(
			sanguis::load::log(),
			sge::log::_1
				<< SGE_TEXT("delay not in global.ini but not in specified in ")
				<< path
				<< SGE_TEXT(" either!")
		);

		throw;
	}
}

}

sanguis::load::model::animation::animation(
	global_parameters const &param,
	sge::parse::ini::entry_vector const &entries)
:
	anim(
		sge::make_shared_ptr<
			sge::sprite::animation_series
		>()
	)
{
	sge::renderer::size_type const
		begin(
			get_entry<
				int	
			>(
				entries,
				SGE_TEXT("begin")
			)
		),
		end(
			get_entry<
				int	
			>(
				entries,
				SGE_TEXT("end")
			)
		);
	
	sge::time::unit const delay(
		load_delay(
			entries,
			param.delay(),
			param.path()
		)
	);
	sge::renderer::lock_rect const area(
		param.tex()->area()
	);

	for(sge::renderer::size_type i = begin; i != end; ++i)
		anim->push_back(
			sge::sprite::animation_entity(
				sge::time::millisecond(
					delay
				),
				sge::texture::const_part_ptr(
					sge::make_shared_ptr<
						sge::texture::part_raw
					>(
						param.tex()->texture(),
						calc_rect(
							area,
							param.cell_size(),
							i
						)
					)
				)
			)
		);
}

sge::sprite::animation_series const &
sanguis::load::model::animation::get() const
{
	return *anim;
}

sanguis::load::model::animation_sound const &
sanguis::load::model::animation::sounds() const
{
	static animation_sound ret;
	return ret; // FIXME
	/*
	if(!sounds_)
		sounds_.reset(
			new animation_sound(
				path,
				ctx));
	return *sounds_;*/
}
