#ifndef SANGUIS_LOAD_MODEL_MODEL_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MODEL_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "part.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/string.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class model {
	typedef std::map<sge::string, part> part_map;
public:
	typedef part_map::value_type     value_type;
	typedef part_map::const_iterator const_iterator;
	typedef part_map::size_type      size_type;

	part const &
	operator[](
		sge::string const &) const;
	const_iterator begin() const;
	const_iterator end() const;
	size_type size() const;
private:
	model(
		sge::filesystem::path const &,
		resource::context const &);
	
	void construct(
		resource::context const &);

	friend class collection;

	sge::filesystem::path const path;
	part_map parts;
};

}
}
}

#endif
