#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <assert.h>
#include "SFML/Graphics.hpp"
#include "ResourceIdentifiers.h"

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
	void load(Identifier id, const std::string& filename);
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	void insertResource(Identifier id, std::unique_ptr<Resource> resource);
};

#include "ResourceHolder.inl"