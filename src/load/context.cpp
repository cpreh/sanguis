#include "context.hpp"
#include "model/object.hpp"
#include "model/context.hpp"
#include "model/collection.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::load::context::context(
	sge::image2d::multi_loader &_il,
	sge::renderer::device_ptr const _rend,
	sge::audio::multi_loader &_ml,
	sge::audio::player_ptr const _ap
)
:
	il_(_il),
	rend_(_rend),
	ml_(_ml),
	ap_(_ap),
	resource_ctx_(
		rend_,
		il_,
		ml_,
		ap_
	),
	model_ctx_(
		resource_ctx_
	)
{}

sanguis::load::context::~context()
{}

sanguis::load::resource::context const &
sanguis::load::context::resources() const
{
	return resource_ctx_;
}

sanguis::load::model::context const &
sanguis::load::context::models() const
{
	return model_ctx_;
}

void
sanguis::load::context::update(
	time_type const _delta
) const
{
	resource_ctx_.update(
		_delta
	);
}

sge::renderer::dim2 const
sanguis::load::context::model_dim(
	fcppt::string const &_model_name
) const
{
	return
		model_ctx_()[
			_model_name
		].dim();
}
