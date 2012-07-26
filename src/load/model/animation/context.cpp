#include <sanguis/load/model/animation/context.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/frame_cache.hpp>
#include <sanguis/load/resource/animation/entity.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sanguis/load/resource/texture_context_impl.hpp>
#include <sanguis/exception.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/ref.hpp>
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

	sge::renderer::texture::planar_shared_ptr const texture(
		texture_context_.value()->result()
	);

	cache_callback_(
		texture->area()
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
				texture,
				sge::texture::const_part_shared_ptr(
					fcppt::make_shared_ptr<
						sge::texture::part_raw_ref
					>(
						fcppt::ref(
							*texture
						),
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
