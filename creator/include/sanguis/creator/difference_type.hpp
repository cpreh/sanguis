#ifndef SANGUIS_CREATOR_DIFFERENCE_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_DIFFERENCE_TYPE_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{

typedef
std::make_signed<
	sanguis::creator::size_type
>::type
difference_type;

}
}

#endif
