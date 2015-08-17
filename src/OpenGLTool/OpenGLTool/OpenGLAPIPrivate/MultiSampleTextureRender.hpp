#ifndef _MT__RENDER__TEXTURE_0_
#define _MT__RENDER__TEXTURE_0_

#include "FunctionTexttureOpenglTool.hpp"
#include "ProgramFunction.hpp"
#include "DrawFunctions.hpp"
#include "FBOTypeGL.hpp"
#include "VertexArrayFunction.hpp"
#include <memory>

namespace gl{

class MultiSampleTextureRender {
	class Data {
	public:
		gl::Program program;
		gl::NamedVertexArrayObject vao;
		~Data() {
			gl::deleteVertexArrays(1, &vao);
			gl::deleteProgram(program);
		}
	};
	std::shared_ptr<Data> data;
	void init() {
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
		constexpr static char fs[] = R"(#version 450
smooth in vec2 tuv;
out vec4 color ;
layout(binding=0) uniform sampler2DMS stex; 
layout(location=1) uniform int sampleSize = 8;
void main(){
ivec2 ts = textureSize( stex );
color = vec4(0,0,0,0);
int i =0;
for( ;i<sampleSize;++i ){
color += texelFetch( stex,ivec2(ts*tuv),i );
}
color /= sampleSize;
}
)";
		data->program = gl::VFProgramLoadSources(vs, fs);
		gl::createVertexArrays(1, &(data->vao));
	}
public:
	MultiSampleTextureRender() {

	}
	void render(gl::NamedTexture texture,GLint samples=8) {
		if (false == data) { init(); }
		data->program.use();
		data->program.bindVertexArray(data->vao);
		data->program.bindTexture( texture, 0, GL_TEXTURE_2D_MULTISAMPLE );
		data->program.setUniform1i( 1, samples );
		using namespace gl::DrawArrays;
		Pack pack( Mode::TRIANGLE_STRIP, 0, 4 );
		gl::draw(pack);
	}
};

}


#endif



