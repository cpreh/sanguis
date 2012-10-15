#ifndef SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/resource/animations_fwd.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


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

	resource::animations const &
	animations() const;
private:
	friend class load::context;

	context(
		sge::renderer::device::core &,
		sge::image2d::system &
	);

	~context();

	fcppt::scoped_ptr<
		resource::textures
	> const textures_;

	fcppt::scoped_ptr<
		resource::animations
	> const animations_;
};

}
}
}

#endif
