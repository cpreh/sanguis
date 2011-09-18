#ifndef SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/resource/animations_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
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
	resource::textures const &
	textures() const;

	resource::sounds const &
	sounds() const;

	resource::animations const &
	animations() const;
private:
	friend class load::context;

	context(
		sge::renderer::device &,
		sge::image2d::multi_loader &,
		sge::audio::multi_loader &,
		sge::audio::player &
	);

	~context();

	fcppt::scoped_ptr<
		resource::textures
	> textures_;

	fcppt::scoped_ptr<
		resource::sounds
	> sounds_;

	fcppt::scoped_ptr<
		resource::animations
	> animations_;
};

}
}
}

#endif
