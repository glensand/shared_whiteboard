#pragma once

#include <memory>
#include <typeinfo>

template <typename T>
size_t ComputeHash(const std::unique_ptr<T> &ptr)
{
	const auto& typeInfo = typeid(ptr.get());
	const auto hashCode = typeInfo.hash_code();

	return hashCode;
}

template <typename T>
size_t ComputeHash()
{
	T* t{ nullptr };
	const auto& typeInfo = typeid(t);
	const auto hashCode = typeInfo.hash_code();

	return hashCode;
}