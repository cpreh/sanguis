#ifndef SANGUIS_ANIMATION_TYPE_HPP_INCLUDED
#define SANGUIS_ANIMATION_TYPE_HPP_INCLUDED

#include <sanguis/animation_type_fwd.hpp>


namespace sanguis
{

enum class animation_type
{
	none,
	attacking,
	walking,
	dying,
	deploying,
	reloading,
	size
};

}

#endif
