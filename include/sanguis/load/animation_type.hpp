#ifndef SANGUIS_LOAD_ANIMATION_TYPE_HPP_INCLUDED
#define SANGUIS_LOAD_ANIMATION_TYPE_HPP_INCLUDED

#include <sanguis/load/animation_type_fwd.hpp>


namespace sanguis
{
namespace load
{

enum class animation_type
{
	none,
	attacking,
	walking,
	dying,
	deploying,
	reloading,
	fcppt_maximum = reloading
};

}
}

#endif
