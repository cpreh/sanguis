#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/perk.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

void sanguis::server::entities::with_perks::add_perk(sanguis::perk_type const _type)
{
  fcppt::optional::from(
      fcppt::container::find_opt_mapped(perks_, _type),
      [this, _type]()
      {
        return fcppt::make_ref(
            perks_
                .insert(std::make_pair(
                    _type,
                    sanguis::server::perks::create(
                        fcppt::make_cref(this->diff_clock()), random_generator_, _type)))
                .first->second);
      })
      .get()
      ->raise_level(*this);
}

sanguis::server::entities::with_perks::~with_perks() = default;

sanguis::server::entities::with_perks::with_perks(
    sanguis::random_generator_ref const _random_generator)
    : random_generator_(_random_generator), perks_()
{
}

void sanguis::server::entities::with_perks::update()
{
  fcppt::optional::maybe_void(
      this->environment(),
      [this](fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        for (auto const &perk : this->perks_)
        {
          perk.second->update(*this, _environment.get());
        }
      });
}
