#ifndef SANGUIS_CREATOR_GENERATOR_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_RESULT_HPP_INCLUDED

#include <sanguis/creator/generator/result_fwd.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sanguis/creator/symbol.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

class result
{
public:
	SANGUIS_CREATOR_SYMBOL
	result(
		geometry::shape_container const &
	);
private:
	geometry::shape_container shapes_;
};

}
}
}

#endif
