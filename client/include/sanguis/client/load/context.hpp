#ifndef SANGUIS_CLIENT_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/model/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		fcppt::log::context &,
		sge::image2d::system &,
		sge::renderer::device::core &,
		sge::audio::loader &,
		sge::audio::player &
	);

	~context();

	sanguis::client::load::resource::context const &
	resources() const;

	sanguis::client::load::model::context const &
	models() const;
private:
	sanguis::client::load::resource::context const resource_ctx_;

	sanguis::client::load::model::context const model_ctx_;
};

}
}
}

#endif
