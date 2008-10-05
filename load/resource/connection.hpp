#ifndef SANGUIS_LOAD_RESOURCE_CONNECTION_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_CONNECTION_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/player_fwd.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class connection : boost::noncopyable
{
	public:
	connection(
		sge::image::loader_ptr,
		sge::renderer::device_ptr,
		sge::audio::multi_loader &,
		sge::audio::player_ptr);
	~connection();
};
}
}
}

#endif
