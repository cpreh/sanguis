#ifndef SANGUIS_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace load
{

class context
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

	sanguis::load::resource::context const &
	resources() const;

	sanguis::load::model::context const &
	models() const;
private:
	sanguis::random_generator random_generator_;

	sanguis::load::resource::context const resource_ctx_;

	sanguis::load::model::context const model_ctx_;
};

}
}

#endif
