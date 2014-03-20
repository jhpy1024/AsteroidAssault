#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

class Buffer
{
public:
    Buffer();
    ~Buffer();

    void init();

    void setData(const std::vector<float>& data);
    int getDataSize() const;

    void bind();

private:
    GLuint m_Buffer;

    int m_DataSize;
};

#endif