#ifndef SANGUIS_CREATOR_GEOMETRY_TRIANGULATE_TRANSFORM_FUNCTION_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_TRIANGULATE_TRANSFORM_FUNCTION_HPP_INCLUDED

#include <fcppt/function/object.hpp>

namespace sanguis
{
namespace creator
{
namespace geometry
{
namespace triangulate
{

template<
	typename ResultContainer
>
struct transform_function
{
private:
	typedef typename ResultContainer::value_type poly_type;

	typedef typename poly_type::value_type vector_type;

	typedef typename vector_type::value_type value_type;
public:
	typedef fcppt::function::object<
		value_type (
			value_type
		)
	> type;
};

}
}
}
}

#endif
