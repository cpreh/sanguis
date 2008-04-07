#include "singleton.hpp"
#include "collection.hpp"
#include <cstddef>

namespace
{

std::size_t refcount = 0;
sanguis::load::model::collection* singleton_ = 0;

}

sanguis::load::model::collection const&
sanguis::load::model::singleton()
{
	if(!singleton_)
		throw sge::exception(SGE_TEXT("No connection to load::model::singleton made!"));
	return *singleton_;
}

sanguis::load::model::connection::connection()
{
	if(refcount++ == 0)
		singleton_ = new collection();
}

sanguis::load::model::connection::~connection()
{
	if(--refcount == 0)
	{
		delete singleton_;
		singleton_ = 0;
	}
}
