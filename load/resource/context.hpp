#ifndef SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{

class context;

namespace resource
{

class textures;
class sounds;
class animations;

class context : boost::noncopyable {
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
		sge::renderer::device_ptr,
		sge::image::loader_ptr,
		sge::audio::multi_loader &,
		sge::audio::player_ptr,
		sge::audio::pool &);
	~context();

	boost::scoped_ptr<
		resource::textures
	> textures_;

	boost::scoped_ptr<
		resource::sounds
	> sounds_;

	boost::scoped_ptr<
		resource::animations
	> animations_;
};

}
}
}

#endif
