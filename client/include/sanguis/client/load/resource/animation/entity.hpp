#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/load/resource/animation/entity_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{
namespace animation
{

class entity
{
public:
	// TODO: Why shared_ptr?
	entity(
		sanguis::duration const &delay,
		sge::texture::const_part_shared_ptr
	);

	sanguis::duration const
	delay() const;

	sge::texture::const_part_shared_ptr
	tex() const;

	// TODO: What does this do?
	void
	tex(
		sge::texture::const_part_shared_ptr
	);

	sge::renderer::dim2 const
	dim() const;
private:
	sanguis::duration delay_;

	sge::texture::const_part_shared_ptr tex_part_;
};

}
}
}
}
}

#endif
