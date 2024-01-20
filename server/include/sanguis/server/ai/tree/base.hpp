#ifndef SANGUIS_SERVER_AI_TREE_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_BASE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/tree/base_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::ai::tree
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  virtual ~base();

  [[nodiscard]] virtual sanguis::server::entities::transfer_result transfer() = 0;

  [[nodiscard]] virtual sanguis::server::ai::status run(sanguis::duration) = 0;
};

}

#endif
