#ifndef SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_CONTEXT_HPP_INCLUDED

#include <sanguis/load/context_fwd.hpp>
#include <sanguis/load/resource/animations_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
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
	sanguis::load::resource::textures const &
	textures() const;

	sanguis::load::resource::animations const &
	animations() const;
private:
	friend class sanguis::load::context;

	context(
		sge::renderer::device::core &,
		sge::image2d::system &
	);

	~context();

	fcppt::scoped_ptr<
		sanguis::load::resource::textures
	> const textures_;

	fcppt::scoped_ptr<
		sanguis::load::resource::animations
	> const animations_;
};

}
}
}

#endif
