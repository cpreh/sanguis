#include <sanguis/random_seed.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/model/object.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>


sanguis::load::context::context(
	sge::image2d::system &_il,
	sge::renderer::device::core &_rend
)
:
	random_generator_(
		sanguis::random_seed()
	),
	resource_ctx_(
		_rend,
		_il
	),
	model_ctx_(
		resource_ctx_,
		random_generator_
	)
{
}

sanguis::load::context::~context()
{
}

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
