#ifndef SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "model.hpp"
#include <fcppt/string.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class collection {
public:
	model const &
	operator[](
		fcppt::string const &) const;
private:
	explicit collection(
		resource::context const &);

	friend class context;

	resource::context const &ctx;

	typedef std::map<
		fcppt::string,
		model
	> model_map;

	mutable model_map models;
};

}
}
}

#endif
