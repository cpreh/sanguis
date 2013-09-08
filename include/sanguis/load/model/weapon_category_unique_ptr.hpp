#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/load/model/weapon_category_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

typedef
std::unique_ptr<
	sanguis::load::model::weapon_category
>
weapon_category_unique_ptr;

}
}
}

#endif