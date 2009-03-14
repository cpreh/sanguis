#include "animation.hpp"
#include "animation_sound.hpp"
#include "../../exception.hpp"
#include "../resource/animations.hpp"
#include "../resource/context.hpp"
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
#include <sge/text.hpp>
#include <boost/variant/get.hpp>
#include <boost/foreach.hpp>

namespace
{

template<
	typename T
>
T entry(
	sge::parse::ini::entry_vector const &e,
	sge::string const &name)
{
	BOOST_FOREACH(
		sge::parse::ini::entry_vector::const_reference r,
		e
	)
		if(r.name == name)
			return boost::get<T>(r.value_);
	throw sanguis::exception(
		SGE_TEXT("entry ")
		+ name
		+ SGE_TEXT(" not found")
	);
}

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

}

sanguis::load::model::animation::animation(
	sge::texture::part_ptr const tex,
	sge::renderer::dim_type const &cell_size,
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
			entry<
				sge::renderer::size_type
			>(
				entries,
				SGE_TEXT("begin")
			)
		),
		end(
			entry<
				sge::renderer::size_type
			>(
				entries,
				SGE_TEXT("end")
			)
		);
	
	sge::time::unit const delay(
		entry<
			sge::time::unit
		>(
			entries,
			SGE_TEXT("delay")
		)
	);

	sge::renderer::lock_rect const area(
		tex->area()
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
						tex->texture(),
						calc_rect(
							area,
							cell_size,
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
