#include "context.hpp"
#include "../global_parameters.hpp"
#include "../frame_cache.hpp"
#include "../../resource/animation/entity.hpp"
#include "../../resource/animation/series.hpp"
#include "../../resource/texture_context_impl.hpp"
#include "../../../exception.hpp"
#include <sge/texture/part_raw.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>

sanguis::load::model::animation::context::context(
	resource::texture_context const &_texture_context,
	frame_cache const &_frame_cache,
	cache_callback const &_cache_callback
)
:
	texture_context_(
		_texture_context
	),
	frame_cache_(
		_frame_cache
	),
	cache_callback_(
		_cache_callback
	),
	is_finished_(
		false
	),
	animation_()
{
}

sanguis::load::model::animation::context::~context()
{
}

void
sanguis::load::model::animation::context::update()
{
	if (is_finished_)
		return;

	if (!texture_context_.value()->update())
		return;
	
	is_finished_ = true;

	animation_ = resource::animation::series();

	sge::texture::part_ptr const part( 
		texture_context_.value()->result()
	);
	
	cache_callback_(
		part->area()
	);

	for(
		frame_cache::const_iterator frame_it(
			frame_cache_.begin()
		);
		frame_it != frame_cache_.end();
		++frame_it
	)
		animation_.push_back(
			resource::animation::entity(
				frame_it->delay(),
				sge::texture::const_part_ptr(
					fcppt::make_shared_ptr<
						sge::texture::part_raw
					>(
						part->texture(),
						frame_it->area()
					)
				)
			)
		);
}

bool
sanguis::load::model::animation::context::is_finished() const
{
	return is_finished_;
}

sanguis::load::resource::animation::series const &
sanguis::load::model::animation::context::result() const
{
	return animation_;
}
