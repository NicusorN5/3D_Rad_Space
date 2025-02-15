/// ------------------------------------------------------------------------------------------------
/// File:   Memory.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <stacktrace>
#include <iostream>

/*
#ifdef _DEBUG

static __int64 _allocCounter = 0;

void* operator new(size_t sz)
{
	std::cout << "[" << _allocCounter << " ]Allocated " << sz << "bytes at" << std::stacktrace::current()[1].description() << "\r\n";
	if (sz == 0)
		++sz; // avoid std::malloc(0) which may return nullptr on success

	if (void* ptr = std::malloc(sz + sizeof(__int64) + alignof(__int64)))
	{
		(*static_cast<__int64*>(ptr)) = _allocCounter;
		_allocCounter++;
		return static_cast<void*>(static_cast<std::byte*>(ptr) + alignof(__int64) + sizeof(__int64));
	}

	throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void* ptr) noexcept
{
	std::cout << "Freed ["<< (*static_cast<__int64*>(ptr)) << "] at address: " << reinterpret_cast<__int64>(ptr) << "\r\n";
	std::free(ptr);
}
#endif
*/