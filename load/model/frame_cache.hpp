#ifndef SANGUIS_LOAD_MODEL_FRAME_CACHE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_FRAME_CACHE_HPP_INCLUDED

#include "frmae_cache_fwd.hpp"
#include "frame_cache_value.hpp"
#include <vector>

namespace sanguis
{
namespace load
{
namespace model
{
class frame_cache
{
	typedef std::vector<frame_cache_value> value_vector;
public:
	typedef value_vector::const_reference const_reference;
	typedef value_vector::const_iterator const_iterator;

	void push_back(
		frame_cache_value const &);
	const_iterator begin() const;
	const_iterator end() const;
	bool empty() const;
private:
	value_vector values_;
};
}
}
}

#endif
