#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/resource/animations_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>


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

	sanguis::client::load::resource::animations const &
	animations() const;
private:
	friend class sanguis::client::load::context;

	context(
		sge::renderer::device::core &,
		sge::image2d::system &,
		sge::audio::loader &,
		sge::audio::player &
	);

	~context();

	fcppt::scoped_ptr<
		sanguis::client::load::resource::textures
	> const textures_;

	fcppt::scoped_ptr<
		sanguis::client::load::resource::animations
	> const animations_;

	fcppt::scoped_ptr<
		sanguis::client::load::resource::sounds
	> const sounds_;
};

}
}
}
}

#endif
