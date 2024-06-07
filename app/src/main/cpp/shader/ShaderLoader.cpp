//
// Created by Dark Matter on 6/6/24.
//

#include "ShaderLoader.h"
ShaderLoader::ShaderLoader() : shaders_() {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    std::string name("default");
    shaders_.insert(std::make_pair(name, shader));
}

 Shader* ShaderLoader::load(const char* name) {
    std::string shaderName(name);
    auto it = shaders_.find(shaderName);
    if (it != shaders_.end()) {
        return it->second.get();
    } else {
        return nullptr; // or handle the case where the shader is not found
    }
}

void ShaderLoader::setNumOfLights(int count) const {
    for (const auto &item: shaders_){
        glUniform1i(item.second->getNumberOfLightsLocation(), count);
    }
}

void ShaderLoader::setNumOfSpotLights(int count) const {
    for (const auto &item: shaders_){
        glUniform1i(item.second->getNumberOfSpotLightsLocation(), count);
    }
}
