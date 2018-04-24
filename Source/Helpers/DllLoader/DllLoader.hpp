#ifndef DLLLOADER_H
#define DLLLOADER_H

#include <memory>
#include <string_view>
#include <map>
#include <boost/dll/import.hpp>
#include <boost/any.hpp>

namespace jukebox {

template<typename T>
std::shared_ptr<T> make_shared_ptr(boost::shared_ptr<T>& ptr)
{
    return std::shared_ptr<T>(ptr.get(), [ptr](T*) mutable {ptr.reset();});
}

class DllLoader
{
public:
    template<class T>
    std::shared_ptr<T> load(std::string_view plugin_name)
    {
        boost::filesystem::path lib_path(boost::filesystem::current_path());
        lib_path.append("Dlls");

        boost::shared_ptr<T> plugin;

        try
        {
            plugin = boost::dll::import<T>(lib_path / plugin_name.data(),
                                           "plugin",
                                           boost::dll::load_mode::append_decorations);

            auto loaded = make_shared_ptr(plugin);
            boost::any stored = loaded;

            plugins[std::string(plugin_name)] = stored;
            return loaded;
        }
        catch(boost::system::system_error& e)
        {
            e.what();
        }

        return {};
    }

    void unload(std::string plugin_name)
    {
        plugins.erase(plugin_name);
    }

private:
    static std::map<std::string, boost::any> plugins;
};

std::map<std::string, boost::any> DllLoader::plugins;

}

#endif //DLLLOADER_H
