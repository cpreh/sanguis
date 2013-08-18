#include <sanguis/load/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/model/object.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>


sanguis::load::context::context(
	sge::image2d::system &_image_loader,
	sge::renderer::device::core &_renderer,
	sge::audio::loader &_audio_loader,
	sge::audio::player &_audio_player
)
:
	resource_ctx_(
		_renderer,
		_image_loader,
		_audio_loader,
		_audio_player
	),
	model_ctx_(
		resource_ctx_
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
