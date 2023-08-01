#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_BASE_HPP_INCLUDED

#include <sanguis/server/entities/property/base_fwd.hpp>
#include <sanguis/server/entities/property/constant.hpp>
#include <sanguis/server/entities/property/linear.hpp>
#include <sanguis/server/entities/property/linear_decrease.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis::server::entities::property
{

class base
{
  FCPPT_NONCOPYABLE(base);

public:
  [[nodiscard]] sanguis::server::entities::property::constant constant() const;

  [[nodiscard]] sanguis::server::entities::property::linear linear() const;

  [[nodiscard]] sanguis::server::entities::property::linear_decrease linear_decrease() const;

  void constant(sanguis::server::entities::property::constant const &);

  void linear(sanguis::server::entities::property::linear const &);

  void linear_decrease(sanguis::server::entities::property::linear_decrease const &);

  virtual ~base();
protected:
  explicit base(sanguis::server::entities::property::value);

  base(base &&) noexcept;

  base &operator=(base &&) noexcept;

private:
  void recalc_max();

  virtual void on_recalc_max(sanguis::server::entities::property::value) = 0;

  sanguis::server::entities::property::value base_;

  sanguis::server::entities::property::constant constant_;

  sanguis::server::entities::property::linear linear_;

  sanguis::server::entities::property::linear_decrease linear_decrease_;
};

}

#endif
