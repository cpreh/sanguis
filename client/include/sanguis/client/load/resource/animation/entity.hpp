#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/load/resource/animation/entity_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		entity
	);
public:
	entity(
		sanguis::duration,
		sge::texture::const_part_unique_ptr &&
	);

	entity(
		entity &&
	);

	entity &
	operator=(
		entity &&
	);

	~entity();

	sanguis::duration const
	delay() const;

	sge::texture::part const &
	texture() const;

	sge::renderer::dim2 const
	dim() const;
private:
	sanguis::duration delay_;

	sge::texture::const_part_unique_ptr texture_;
};

}
}
}
}
}

#endif
