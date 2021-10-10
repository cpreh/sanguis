#ifndef SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/client/load/model/object_fwd.hpp>
#include <sanguis/client/load/resource/context_cref.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load::model
{

class collection
{
  FCPPT_NONMOVABLE(collection);

public:
  [[nodiscard]] sanguis::client::load::model::object const &
  operator[](sanguis::load::model::path const &) const;

  [[nodiscard]] collection(
      fcppt::log::context_reference, sanguis::client::load::resource::context_cref);

  ~collection();

private:
  mutable fcppt::log::object log_;

  sanguis::client::load::resource::context_cref const resources_;

  using model_unique_ptr = fcppt::unique_ptr<sanguis::client::load::model::object>;

  using model_map = std::map<sanguis::load::model::path, model_unique_ptr>;

  mutable model_map models_;
};

}

#endif
