#ifndef SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "model.hpp"
#include <sge/string.hpp>
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
		sge::string const &) const;
private:
	explicit collection(
		resource::context const &);

	friend struct context;

	resource::context const &ctx;

	typedef std::map<
		sge::string,
		model
	> model_map;

	mutable model_map models;
};

}
}
}

#endif
