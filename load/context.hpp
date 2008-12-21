#ifndef SANGUIS_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_HPP_INCLUDED

#include "model/context.hpp"
#include "resource/context.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{

class context : boost::noncopyable {
public:
	context(
		sge::image::loader_ptr,
		sge::renderer::device_ptr,
		sge::audio::multi_loader &,
		sge::audio::player_ptr,
		sge::audio::pool_ptr);
	~context();

	resource::context const &
	resources() const;

	model::context const &
	models() const;
private:
	sge::image::loader_ptr const il;
	sge::renderer::device_ptr const rend;
	sge::audio::multi_loader &ml;
	sge::audio::player_ptr const ap;
	sge::audio::pool_ptr const pool;

	resource::context const resource_ctx;
	model::context const model_ctx;
};

}
}

#endif
