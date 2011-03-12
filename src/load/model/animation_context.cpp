#include "animation_context.hpp"
#include "global_parameters.hpp"
#include "frame_cache.hpp"
#include "../resource/texture_context_impl.hpp"
#include "../../exception.hpp"
#include <sge/sprite/animation/series.hpp>
#include <sge/sprite/animation/entity.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <sge/time/unit.hpp>
#include <boost/foreach.hpp>

sanguis::load::model::animation_context::animation_context(
	resource::texture_context const &_texture_context,
	frame_cache const &_frame_cache,
	cache_callback const &_cache_callback
)
:
	texture_context_(
		_texture_context),
	frame_cache_(
		_frame_cache),
	cache_callback_(
		_cache_callback),
	is_finished_(
		false),
	animation_()
{
}

void
sanguis::load::model::animation_context::update()
{
	if (is_finished_)
		return;

	if (!texture_context_.value()->update())
		return;
	
	is_finished_ = true;

	animation_ = sge::sprite::animation::series();

	sge::texture::part_ptr const part( 
		texture_context_.value()->result()
	);
	
	cache_callback_(
		t->area()
	);

	BOOST_FOREACH(
		frame_cache::const_reference frame,
		frame_cache_
	)
		animation_.push_back(
			sge::sprite::animation::entity(
				sge::time::millisecond(
					frame.delay()
				),
				sge::texture::const_part_ptr(
					fcppt::make_shared_ptr<
						sge::texture::part_raw
					>(
						part->texture(),
						frame.area()
					)
				)
			)
		);
}

bool
sanguis::load::model::animation_context::is_finished() const
{
	return is_finished_;
}

sge::sprite::animation::series const &
sanguis::load::model::animation_context::result() const
{
	return animation_;
}
