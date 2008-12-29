#include "environment.hpp"

sanguis::draw::environment::environment(
	insert_callback const &insert_,
	load::context const &context_,
	draw::system &system_)
:
	insert_(insert_),
	context_(context_),
	system_(system_)
{}
	
sanguis::draw::insert_callback const &
sanguis::draw::environment::insert() const
{
	return insert_;
}

sanguis::load::context const &
sanguis::draw::environment::context() const
{
	return context_;
}

sanguis::draw::system &
sanguis::draw::environment::system() const
{
	return system_;
}
