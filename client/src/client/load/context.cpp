#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/context.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/player_ref.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/log/context_reference.hpp>


sanguis::client::load::context::context(
	fcppt::log::context_reference const _log_context,
	sge::image2d::system_ref const _image_loader,
	sge::renderer::device::core_ref const _renderer,
	sge::audio::loader_ref const _audio_loader,
	sge::audio::player_ref const _audio_player
)
:
	resource_ctx_(
		_log_context,
		_renderer,
		_image_loader,
		_audio_loader,
		_audio_player
	),
	model_ctx_(
		_log_context,
		resource_ctx_
	)
{
}

sanguis::client::load::context::~context()
= default;

sanguis::client::load::resource::context const &
sanguis::client::load::context::resources() const
{
	return
		resource_ctx_;
}

sanguis::client::load::model::context const &
sanguis::client::load::context::models() const
{
	return
		model_ctx_;
}
