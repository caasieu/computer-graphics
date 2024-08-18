#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

int main(int argc, char * argv[]) {


    // Get the current path of the project
    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path parent_path = current_path.parent_path();

    std::ifstream t("shaders/pontinho_1.vert");
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout<<buffer.str()<<std::endl;
    
    return 0;
}   

