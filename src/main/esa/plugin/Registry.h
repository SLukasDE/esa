/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESA_PLUGIN_REGISTRY_H_
#define ESA_PLUGIN_REGISTRY_H_

#include <esa/object/Object.h>
#include <esa/plugin/BasePlugin.h>
#include <esa/plugin/exception/PluginNotFound.h>
#include <esa/plugin/Library.h>
#include <esa/plugin/Plugin.h>

#include <map>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <set>
#include <string>
#include <typeindex>
#include <utility>
#include <vector>

#define DO_QUOTE(X)                  #X
#define QUOTE(X)                     DO_QUOTE(X)

#ifndef TRANSFORMER_ARTEFACT_ID
#define TRANSFORMER_ARTEFACT_ID
//#define TRANSFORMER_ARTEFACT_ID           esl
#endif

#ifndef TRANSFORMER_ARTEFACT_NAME
#define TRANSFORMER_ARTEFACT_NAME
//#define TRANSFORMER_ARTEFACT_NAME         esl
#endif

#ifndef TRANSFORMER_ARTEFACT_VERSION
#define TRANSFORMER_ARTEFACT_VERSION
//#define TRANSFORMER_ARTEFACT_VERSION      1.0.0
#endif

#ifndef TRANSFORMER_ARTEFACT_API_VERSION
#define TRANSFORMER_ARTEFACT_API_VERSION
//#define TRANSFORMER_ARTEFACT_API_VERSION  1
#endif

#ifndef TRANSFORMER_ARTEFACT_VARIANT
#define TRANSFORMER_ARTEFACT_VARIANT
#endif

#ifndef TRANSFORMER_ARTEFACT_ARCHITECTURE
#define TRANSFORMER_ARTEFACT_ARCHITECTURE
#endif

#ifndef TRANSFORMER_ARTEFACT_LICENSE
#define TRANSFORMER_ARTEFACT_LICENSE
#endif

namespace esa {
inline namespace v1_6 {
namespace plugin {

class Registry final {
	friend class Library;
public:
	template <typename Interface>
	using Factory = std::unique_ptr<Interface> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	using BasePlugins = std::map<std::string, std::unique_ptr<const BasePlugin>>;

	~Registry();

	static Registry& get();
	static void set(Registry& registry);
	static void cleanup();

	template <typename Object>
	static Object* findObject();

	template <typename Object>
	static void setObject(std::unique_ptr<Object> object);

	void dump(std::ostream& ostream) const;

	template <typename Interface>
	std::unique_ptr<Interface> create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) const;

	template <class Interface>
	const BasePlugins& getPlugins() const;
	const BasePlugins& getPlugins(std::type_index typeIndex) const;

	template <typename Interface>
	const Factory<Interface> findFactory() const noexcept;

	template <typename Interface>
	const Factory<Interface> findFactory(const std::string& implementation) const noexcept;

	template <typename Interface>
	const Factory<Interface> getFactory() const;

	template <typename Interface>
	const Factory<Interface> getFactory(const std::string& implementation) const;

	template <class Interface>
	const Plugin<Interface>* findPlugin() const noexcept;

	template <class Interface>
	const Plugin<Interface>* findPlugin(const std::string& implementation) const noexcept;

	template <class Interface>
	const Plugin<Interface>& getPlugin() const;

	template <class Interface>
	const Plugin<Interface>& getPlugin(const std::string& implementation) const;

	template <class Interface>
	void addPlugin(const std::string& implementation, std::unique_ptr<Interface> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&));

	template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*CreateFunction)(const std::vector<std::pair<std::string, std::string>>&)>
	void addPlugin(const std::string& implementation);
/*
	template <class Interface>
	void copyPlugin(const std::string& implementationSource, const std::string& implementationDestination);
*/
	void loadPlugin(const std::string& path, const char* data = 0);
	void loadPlugin(std::unique_ptr<Library> library, const char* data = 0);

private:
	Registry() = default;

	const BasePlugin* findBasePlugin(const std::string& implementation, std::type_index typeIndex) const noexcept;
	const BasePlugin* findBasePlugin(std::type_index typeIndex) const noexcept;

	template <class Interface, class Implementation>
	static std::unique_ptr<Interface> createImplementationFunction(const std::vector<std::pair<std::string, std::string>>& settings);

	template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)>
	static std::unique_ptr<Interface> createInterface(const std::vector<std::pair<std::string, std::string>>& settings);

	std::vector<std::unique_ptr<Library>> libraries;

	using TypePlugins = std::map<std::type_index, BasePlugins>;
	TypePlugins typePlugins;

	std::map<std::type_index, std::unique_ptr<object::Object>> objects;
};


template<typename Object>
Object* Registry::findObject() {
	auto iter = get().objects.find(typeid(Object));
	return (iter == get().objects.end()) ? nullptr : static_cast<Object*>(iter->second.get());
}

template<typename Object>
void Registry::setObject(std::unique_ptr<Object> object) {
	if(object) {
		get().objects[typeid(Object)] = std::move(object);
	}
	else {
		get().objects.erase(typeid(Object));
	}
}

template <typename Interface>
std::unique_ptr<Interface> Registry::create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) const {
	return getFactory<Interface>(implementation)(settings);
}

template <class Interface>
const Registry::BasePlugins& Registry::getPlugins() const {
	return getPlugins(typeid(Interface));
}

template <typename Interface>
const Registry::Factory<Interface> Registry::findFactory() const noexcept {
	const Plugin<Interface>* plugin = findPlugin<Interface>();
	return plugin ? plugin->create : nullptr;
}

template <typename Interface>
const Registry::Factory<Interface> Registry::findFactory(const std::string& implementation) const noexcept {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);
	return plugin ? plugin->create : nullptr;
}

template <typename Interface>
const Registry::Factory<Interface> Registry::getFactory() const {
	const Plugin<Interface>* plugin = findPlugin<Interface>();
	if(!plugin) {
		throw plugin::exception::PluginNotFound(typeid(Interface));
	}

	if(!plugin->create) {
		throw std::runtime_error("Cannot get factory for type \"" + std::string(typeid(Interface).name()) + "\"");
	}
	return plugin->create;
}

template <typename Interface>
const Registry::Factory<Interface> Registry::getFactory(const std::string& implementation) const {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);
	if(!plugin) {
		throw plugin::exception::PluginNotFound(typeid(Interface), implementation);
	}

	if(!plugin->create) {
		throw std::runtime_error("Cannot get factory for implementation \"" + implementation + "\" and type \"" + std::string(typeid(Interface).name()) + "\"");
	}
	return plugin->create;
}

template <class Interface>
const Plugin<Interface>* Registry::findPlugin() const noexcept {
	return static_cast<const Plugin<Interface>*>(findBasePlugin(typeid(Interface)));
}

template <class Interface>
const Plugin<Interface>* Registry::findPlugin(const std::string& implementation) const noexcept {
	return static_cast<const Plugin<Interface>*>(findBasePlugin(implementation, typeid(Interface)));
}

template <class Interface>
const Plugin<Interface>& Registry::getPlugin() const {
	const Plugin<Interface>* plugin = findPlugin<Interface>();

	if(plugin == nullptr) {
		throw plugin::exception::PluginNotFound(typeid(Interface));
	}

	return *plugin;
}

template <class Interface>
const Plugin<Interface>& Registry::getPlugin(const std::string& implementation) const {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);

	if(plugin == nullptr) {
		throw plugin::exception::PluginNotFound(typeid(Interface), implementation);
	}

	return *plugin;
}

template <class Interface>
void Registry::addPlugin(const std::string& implementation, std::unique_ptr<Interface> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)) {
	std::unique_ptr<const BasePlugin> basePlugin(new Plugin<Interface>(implementation, createFunction));
	typePlugins[typeid(Interface)][implementation] = std::move(basePlugin);
}

template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*CreateFunction)(const std::vector<std::pair<std::string, std::string>>&)>
void Registry::addPlugin(const std::string& implementation) {
	//typePlugins[typeid(Interface)][implementation] = std::unique_ptr<const BasePlugin>(new Plugin<Interface>(implementation, typeid(Interface) == typeid(ReturnValue) ? CreateFunction : createInterface<Interface, ReturnValue, CreateFunction>));
	typePlugins[typeid(Interface)][implementation] = std::unique_ptr<const BasePlugin>(new Plugin<Interface>(implementation, createInterface<Interface, ReturnValue, CreateFunction>));
}

/*
template <class Interface>
void Registry::copyPlugin(const std::string& implementationSource, const std::string& implementationDestination) {
	addPlugin<Interface>(implementationDestination, getPlugin<Interface>(implementationSource).create);
}
*/
template <class Interface, class Implementation>
std::unique_ptr<Interface> Registry::createImplementationFunction(const std::vector<std::pair<std::string, std::string>>& settings) {
	return std::unique_ptr<Interface>(new Implementation(settings));
}

template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)>
std::unique_ptr<Interface> Registry::createInterface(const std::vector<std::pair<std::string, std::string>>& settings) {
	return createFunction(settings);
}

} /* namespace plugin */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_PLUGIN_REGISTRY_H_ */
