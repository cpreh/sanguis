#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/stack.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeindex>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities
{

class with_buffs : public virtual sanguis::server::entities::base,
                   public virtual sanguis::server::entities::ifaces::with_id
{
  FCPPT_NONMOVABLE(with_buffs);

public:
  void add_buff(sanguis::server::buffs::unique_ptr &&);

  void remove_buff(sanguis::server::buffs::buff & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  ~with_buffs() override;

protected:
  with_buffs();

  void update() override;

  [[nodiscard]] sanguis::buff_type_vector buff_types() const;

private:
  using buff_map = std::unordered_map<std::type_index, sanguis::server::buffs::stack>;

  buff_map buffs_;
};

}

#endif
