#ifndef SANGUIS_MODEL_PART_HPP_INCLUDED
#define SANGUIS_MODEL_PART_HPP_INCLUDED

#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <sanguis/model/symbol.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <sanguis/model/weapon_category_map.hpp>
#include <sanguis/model/weapon_category_name_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis::model
{

class part
{
  FCPPT_NONCOPYABLE(part);

public:
  part();

  part(sanguis::model::weapon_category_map &&, sanguis::model::optional_image_name &&);

  SANGUIS_MODEL_SYMBOL
  part(part &&) noexcept;

  SANGUIS_MODEL_SYMBOL
  part &operator=(part &&) noexcept;

  SANGUIS_MODEL_SYMBOL
  ~part();

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::weapon_category &
  weapon_category(sanguis::model::weapon_category_name const &);

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::weapon_category const &
  weapon_category(sanguis::model::weapon_category_name const &) const;

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::weapon_category &
  operator[](sanguis::model::weapon_category_name const &);

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::weapon_category_map &weapon_categories();

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::weapon_category_map const &
  weapon_categories() const;

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::optional_image_name const &image_name() const;

private:
  sanguis::model::weapon_category_map weapon_categories_;

  sanguis::model::optional_image_name image_name_;
};

}

#endif
