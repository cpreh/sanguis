#ifndef SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include "../context_fwd.hpp"
#include "textures_fwd.hpp"
#include "sounds_fwd.hpp"
#include "../../time_type.hpp"
#include "animations_fwd.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/multi_loader.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class context {
	FCPPT_NONCOPYABLE(context)
public:
	resource::textures const &
	textures() const;

	resource::sounds const &
	sounds() const;

	resource::animations const &
	animations() const;

	void update(
		time_type) const;
private:
	friend class load::context;

	context(
		sge::renderer::device_ptr,
		sge::image::loader_ptr,
		sge::multi_loader<
			sge::audio::loader,
			sge::audio::file,
			sge::audio::exception
		> &,
		sge::audio::player_ptr,
		sge::audio::pool &);
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
