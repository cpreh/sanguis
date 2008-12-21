#include "context.hpp"

sanguis::load::context::context(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const ap,
	sge::audio::pool_ptr const pool)
:
	il(il),
	rend(rend),
	ml(ml),
	ap(ap),
	pool(pool),
	resource_ctx(
		rend,
		il,
		ml,
		ap,
		pool),
	model_ctx(
		resource_ctx)
{}

sanguis::load::context::~context()
{}

sanguis::load::resource::context const &
sanguis::load::context::resources() const
{
	return resource_ctx;
}

sanguis::load::model::context const &
sanguis::load::context::models() const
{
	return model_ctx;
}
