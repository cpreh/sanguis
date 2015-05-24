#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	sanguis::client::load::resource::textures const &
	textures() const;

	sanguis::client::load::resource::sounds const &
	sounds() const;
private:
	friend class sanguis::client::load::context;

	context(
		sge::renderer::device::core &,
		sge::image2d::system &,
		sge::audio::loader &,
		sge::audio::player &
	);

	~context();

	fcppt::unique_ptr<
		sanguis::client::load::resource::textures
	> const textures_;

	fcppt::unique_ptr<
		sanguis::client::load::resource::sounds
	> const sounds_;
};

}
}
}
}

#endif
