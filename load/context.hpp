#ifndef SANGUIS_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_HPP_INCLUDED

#include "model/context.hpp"
#include "resource/context.hpp"
#include "../time_type.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace load
{

class context {
	SGE_NONCOPYABLE(context)
public:
	context(
		sge::image::loader_ptr,
		sge::renderer::device_ptr,
		sge::audio::multi_loader &,
		sge::audio::player_ptr,
		sge::audio::pool &);
	~context();

	resource::context const &
	resources() const;

	model::context const &
	models() const;

	void update(time_type) const;
private:
	sge::image::loader_ptr const il;
	sge::renderer::device_ptr const rend;
	sge::audio::multi_loader &ml;
	sge::audio::player_ptr const ap;
	sge::audio::pool &pool;

	resource::context const resource_ctx;
	model::context const model_ctx;
};

}
}

#endif
