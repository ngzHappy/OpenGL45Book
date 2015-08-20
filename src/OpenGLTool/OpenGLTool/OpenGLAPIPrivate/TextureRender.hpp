#ifndef _A__RENDER__TEXTURE_01_
#define _A__RENDER__TEXTURE_01_

#include "FunctionTexttureOpenglTool.hpp"
#include "ProgramFunction.hpp"
#include "DrawFunctions.hpp"
#include "FBOTypeGL.hpp"
#include "VertexArrayFunction.hpp"
#include <memory>

namespace gl {

class TextureRenderRectangle {
    class Data{
    public:
        gl::Program program;
		gl::NamedVertexArrayObject vao;
        ~Data(){
			gl::deleteVertexArrays(1, &vao);
			gl::deleteProgram( program);
		}
    };
    std::shared_ptr<Data> data;
    void init(){
        data = std::shared_ptr<Data>(new Data);
		constexpr static char vs[] = R"(#version 450
uniform mat4 points = mat4(
-1,1,0,1,
-1,-1,0,1,
1,1,0,1,
1,-1,0,1
);
smooth out vec2 tuv;
void main(){
gl_Position = points[gl_VertexID];
tuv = gl_Position.xy/2+0.5;
}
)";
        constexpr static char fs[] = R"f(#version 450
smooth in vec2 tuv;
out vec4 color ;
layout(binding=0) uniform sampler2DRect stex; 
void main(){
ivec2 ts = textureSize(stex);
color = texelFetch( stex,ivec2(ts*tuv) );
}
)f";
		data->program = gl::VFProgramLoadSources(vs,fs);
		gl::createVertexArrays(1, &(data->vao));
    }
public:
	TextureRenderRectangle(){
        
    }
    void render( gl::NamedTexture texture ){
		if (false == data) { init(); }
		data->program.use();
		data->program.bindVertexArray(data->vao);
		data->program.bindTexture(texture,0, GL_TEXTURE_RECTANGLE);
		using namespace gl::DrawArrays;
		Pack pack(Mode::TRIANGLE_STRIP,0,4);
		gl::draw(pack);
    }
};

}

#endif
