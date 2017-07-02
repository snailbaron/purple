#include <string>
#include <cassert>
#include <filesystem>
#include <tclap/CmdLine.h>
#include <iostream>


namespace fs = std::experimental::filesystem;

class ResourceFile {
public:
    ResourceFile(const std::string& path);

private:
    fs::path _path;
};


class BitmapResource {
private:
    
};





void packResources(const std::string& sourceDir, const std::string& targetDir)
{

    for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
        
    }
}

int main(int argc, char* argv[])
{
    try {
        TCLAP::CmdLine cmdLine("Pack resources");

        TCLAP::ValueArg<std::string> bitmaps(
            "b", "bitmaps",
            "Bitmaps location",
            false, "", "string", cmdLine);
        TCLAP::ValueArg<std::string> animations(
            "a", "animations",
            "Animations location",
            false, "", "string", cmdLine);

        cmdLine.parse(argc, argv);

        
    } catch (TCLAP::ArgException&) {
        std::cerr << "ArgException" << std::endl;
        return 1;
    }
}