#ifndef SANGUIS_CLIENT_LOAD_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/load/model/object_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <sanguis/client/load/model/part_result.hpp>
#include <sanguis/client/load/resource/context_cref.hpp>
#include <sanguis/model/cell_size.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load::model
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  using const_iterator = sanguis::client::load::model::part_map::const_iterator;

  using size_type = sanguis::client::load::model::part_map::size_type;

  object(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      std::filesystem::path &&,
      sanguis::client::load::resource::context_cref);

  ~object();

  [[nodiscard]] sanguis::client::load::model::part const &operator[](fcppt::string const &) const;

  [[nodiscard]] sanguis::client::load::model::part const &
  random_part(sanguis::random_generator & // NOLINT(google-runtime-references)
  ) const; // NOLINT(google-runtime-references)

  [[nodiscard]] size_type size() const;

  [[nodiscard]] const_iterator begin() const;

  [[nodiscard]] const_iterator end() const;

  [[nodiscard]] sanguis::model::cell_size cell_size() const;

private:
  [[nodiscard]] sanguis::client::load::model::part_map const &parts() const;

  std::filesystem::path const path_;

  sanguis::client::load::model::part_result const part_result_;

  using part_map_distribution =
      fcppt::random::distribution::basic<fcppt::random::distribution::parameters::uniform_int<
          sanguis::client::load::model::part_map::size_type>>;

  using part_rand = fcppt::random::variate<sanguis::random_generator, part_map_distribution>;

  using optional_part_rand = fcppt::optional::object<part_rand>;

  mutable optional_part_rand random_part_;
};

}

#endif
