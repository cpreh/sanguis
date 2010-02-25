#ifndef SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include "collection_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include "object.hpp"
#include <fcppt/string.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class collection
{
public:
	object const &
	operator[](
		fcppt::string const &
	) const;
private:
	explicit collection(
		resource::context const &
	);

	friend class context;

	resource::context const &ctx;

	typedef std::map<
		fcppt::string,
		object	
	> model_map;

	mutable model_map models;
};

}
}
}

#endif
