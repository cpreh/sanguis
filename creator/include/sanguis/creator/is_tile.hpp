#ifndef SANGUIS_CREATOR_IS_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_IS_TILE_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct is_tile
:
std::false_type
{
};

template<>
struct is_tile<
	sanguis::creator::tile
>
:
std::true_type
{
};

template<>
struct is_tile<
	sanguis::creator::background_tile
>
:
std::true_type
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
