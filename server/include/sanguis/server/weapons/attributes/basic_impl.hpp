#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_BASIC_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_BASIC_IMPL_HPP_INCLUDED

#include <sanguis/server/weapons/attributes/basic_decl.hpp> // IWYU pragma: export
#include <fcppt/optional/maybe.hpp>

template <typename Wrapped>
sanguis::server::weapons::attributes::basic<Wrapped>::basic(Wrapped const _base)
    : base_(_base), extra_()
{
}

template <typename Wrapped>
void sanguis::server::weapons::attributes::basic<Wrapped>::extra(Wrapped const _extra)
{
  extra_ = optional_extra(_extra);
}

template <typename Wrapped>
Wrapped sanguis::server::weapons::attributes::basic<Wrapped>::base() const
{
  return base_;
}

template <typename Wrapped>
typename sanguis::server::weapons::attributes::basic<Wrapped>::optional_extra
sanguis::server::weapons::attributes::basic<Wrapped>::extra() const
{
  return extra_;
}

template <typename Wrapped>
Wrapped sanguis::server::weapons::attributes::basic<Wrapped>::value() const
{
  return fcppt::optional::maybe(
      this->extra(),
      [this] { return this->base(); },
      [this](Wrapped const _extra) { return this->base() + _extra; });
}

#endif
