#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
    uint32_t LoadTexture(const std::string& filePath);
    GLuint GetProgramID() const { return m_programID; }

    // NEW: Add this function declaration
    void UseProgram() const;

    void setMat4Value(const std::string& name, const glm::mat4& value) const;
    void setVec4Value(const std::string& name, const glm::vec4& value) const;
    void setVec3Value(const std::string& name, const glm::vec3& value) const;
    void setVec2Value(const std::string& name, const glm::vec2& value) const;
    void setFloatValue(const std::string& name, float value) const;
    void setBoolValue(const std::string& name, bool value) const;
    void setIntValue(const std::string& name, int value) const;

    inline void use() const { glUseProgram(m_programID); }

private:
    GLuint m_programID;
};
