#ifndef SANGUIS_SERVER_AI_BEHAVIOR_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_BASE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::ai::behavior
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  explicit base(sanguis::server::ai::context_ref);

public:
  virtual ~base() = 0;

  [[nodiscard]] virtual bool start() = 0;

  [[nodiscard]] virtual sanguis::server::ai::status update(sanguis::duration) = 0;

  [[nodiscard]] virtual sanguis::server::entities::transfer_result transfer();

  [[nodiscard]] sanguis::server::ai::context &context();

  [[nodiscard]] sanguis::server::ai::context const &context() const;

  [[nodiscard]] sanguis::server::entities::with_ai &me();

  [[nodiscard]] sanguis::server::entities::with_ai const &me() const;

private:
  sanguis::server::ai::context_ref const context_;
};

}

#endif
