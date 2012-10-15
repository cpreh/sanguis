#ifndef SANGUIS_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <sanguis/load/context_base.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
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
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		sge::image2d::system &,
		sge::renderer::device::core &
	);

	~context();

	resource::context const &
	resources() const;

	model::context const &
	models() const;
private:
	// context_base overrides
	sge::renderer::dim2 const
	model_dim(
		fcppt::string const &
	) const;

	sge::image2d::system &il_;

	sge::renderer::device::core &rend_;

	sanguis::random_generator random_generator_;

	resource::context const resource_ctx_;

	model::context const model_ctx_;
};

}
}

#endif
