#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/server/buffs/buff_fwd.hpp> // IWYU pragma: keep
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::buffs
{

class buff
{
  FCPPT_NONMOVABLE(buff);

public:
  [[nodiscard]] virtual sanguis::buff_type type() const = 0;

  virtual void add();

  virtual void remove();

  virtual void update();

  virtual ~buff() = 0;

  [[nodiscard]]
  // Only compares other buffs with the same typeid
  virtual bool
  greater(sanguis::server::buffs::buff const &) const = 0;

protected:
  buff();

  FCPPT_DECLARE_STRONG_TYPEDEF(bool, added);

private:
  virtual void apply(sanguis::server::buffs::buff::added);
};

}

#endif
