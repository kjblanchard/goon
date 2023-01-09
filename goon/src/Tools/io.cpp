#include <gnpch.hpp>
#include <Tools/io.hpp>
#include <Goon/Log.hpp>


namespace Goon {

    std::string ReadFromFile(std::string &filepath)
    {
        std::ifstream source(filepath, std::ios::binary);
        std::string result;
        if(!source)
        {
            GN_CORE_WARN("Could not open file at path {0}", filepath);
            return result;
        }
        source.seekg(0, std::ios::end);
        result.resize(source.tellg());
        source.seekg(0, std::ios::beg);
        source.read(&result[0], result.size());
        return result;
    }

}