#ifndef SANGUIS_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_HPP_INCLUDED

#include "context_base.hpp"
#include "model/context.hpp"
#include "resource/context.hpp"
#include "../time_type.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace load
{

class context
:
	public context_base
{
	FCPPT_NONCOPYABLE(context)
public:
	context(
		sge::image::multi_loader &,
		sge::renderer::device_ptr,
		sge::audio::multi_loader &,
		sge::audio::player_ptr,
		sge::audio::pool &
	);

	~context();

	resource::context const &
	resources() const;

	model::context const &
	models() const;

	void
	update(
		time_type
	) const;
private:
	// context_base overrides
	sge::renderer::dim_type const
	model_dim(
		fcppt::string const &
	) const;

	sge::image::multi_loader &il;
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
