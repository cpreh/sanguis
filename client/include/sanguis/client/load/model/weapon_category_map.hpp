#ifndef SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/load/model/weapon_category_unique_ptr.hpp>
#include <fcppt/optional/comparison.hpp> // IWYU pragma: keep
#include <fcppt/optional/std_hash.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load::model
{

using weapon_category_map = std::unordered_map<
    sanguis::optional_primary_weapon_type,
    sanguis::client::load::model::weapon_category_unique_ptr>;

}

#endif
