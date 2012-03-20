#include <sanguis/random_seed.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <fcppt/math/dim/object_impl.hpp>

sanguis::load::context::context(
	sge::image2d::system &_il,
	sge::renderer::device &_rend,
	sge::audio::loader &_ml,
	sge::audio::player &_ap
)
:
	il_(_il),
	rend_(_rend),
	ml_(_ml),
	ap_(_ap),
	random_generator_(
		sanguis::random_seed()
	),
	resource_ctx_(
		rend_,
		il_,
		ml_,
		ap_
	),
	model_ctx_(
		resource_ctx_,
		random_generator_
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
