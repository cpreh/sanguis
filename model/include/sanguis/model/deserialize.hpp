#ifndef SANGUIS_MODEL_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MODEL_DESERIALIZE_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sanguis/model/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{

SANGUIS_MODEL_SYMBOL
sanguis::model::object
deserialize(
	std::filesystem::path const &
);

}
}

#endif
