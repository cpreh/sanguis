#ifndef SANGUIS_LOAD_PARTICLE_RANDOM_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_RANDOM_ANIMATION_HPP_INCLUDED

#include "animation_container.hpp"
#include <sge/random/uniform.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace particle
{

class animation;

class random_animation : boost::noncopyable {
public:
	animation const &
	operator()() const;

	explicit random_animation(
		animation_container const &);
private:
	animation_container const &animations_;

	mutable sge::random::uniform<
		animation_container::size_type
	> rng;
};

}
}
}

#endif
