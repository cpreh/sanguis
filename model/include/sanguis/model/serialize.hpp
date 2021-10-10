#ifndef SANGUIS_MODEL_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MODEL_SERIALIZE_HPP_INCLUDED

#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::model
{

SANGUIS_MODEL_SYMBOL
void serialize(std::filesystem::path const &, sanguis::model::object const &);

}

#endif
