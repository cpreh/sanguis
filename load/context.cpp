#include "context.hpp"
#include "model/object.hpp"
#include "model/context.hpp"
#include "model/collection.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::load::context::context(
	sge::image::multi_loader &il,
	sge::renderer::device_ptr const rend,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const ap,
	sge::audio::pool &pool
)
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
		pool
	),
	model_ctx(
		resource_ctx
	)
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

void
sanguis::load::context::update(
	time_type const delta
) const
{
	resource_ctx.update(
		delta
	);
}

sge::renderer::dim_type const
sanguis::load::context::model_dim(
	fcppt::string const &model_name_
) const
{
	return
		model_ctx()[
			model_name_
		].dim();
}
