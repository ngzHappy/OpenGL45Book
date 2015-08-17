#ifndef _0_CALLBACK__MODEL__LOADER__
#define _0_CALLBACK__MODEL__LOADER__

#include "OpenGLAPIPrivate/BaseType.hxx"
#include "ModelLoader.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

#ifdef QT_CORE_LIB
#include <QImage>
#endif

namespace gl {

class VertexNormalElementCallBack :
	public ModelLoaderCallBack {
	class ThisPrivate;
public:
	ThisPrivate * thisp = 0;
	virtual ~VertexNormalElementCallBack();
	VertexNormalElementCallBack();

	typedef std::uint32_t IndexType;
	class Face {
	public:
		union {
			struct {
				IndexType first;
				IndexType second;
				IndexType third;
			};
			IndexType values[3];
		};
	};

	virtual void begin()                               override;
	virtual void findAFace(FaceType)                   override;
	virtual void findPoint(int, float, float, float)   override;
	virtual void findNormal(int, float, float, float)  override;
	virtual void endFindAFace(FaceType)                override;
	virtual void end()                                 override;

	bool loadFile(const std::string &) override;
	bool saveFile(const std::string &, const std::string & = "")const override;

	std::vector<gl::Float6> pointNormal;
	std::vector<Face> triangles;

	float xMax, yMax, zMax;
	float xMin, yMin, zMin;
};

class VertexTextureNormalElementCallBack :
    public ModelLoaderCallBack {
    class ThisPrivate;
public:
    ThisPrivate * thisp = 0;
    virtual ~VertexTextureNormalElementCallBack();
    VertexTextureNormalElementCallBack();

    typedef std::uint32_t IndexType;
    class Face {
    public:
        union {
            struct {
                IndexType first;
                IndexType second;
                IndexType third;
            };
            IndexType values[3];
        };
    };

    virtual void begin()                                  override ;
    virtual void findTextures(std::map<int, std::string>) override ;
    virtual void findAFace(FaceType)                      override ;
    virtual void findPoint(int, float, float, float)      override ;
    virtual void findNormal(int, float, float, float)     override ;
    virtual void findTexture(int, float, float, int)      override ;
    virtual void endFindAFace(FaceType)                   override ;
    virtual void end()                                    override ;

    bool loadFile(const std::string &) override;
    bool saveFile(const std::string &,const std::string & = "")const override;

    typedef std::vector<gl::Float8> VertexType           ;
	typedef std::map<int, VertexType> PointNormalTexture ;
    typedef std::vector<Face>  FacesType                 ;
	typedef std::map<int, FacesType>  Triangles          ;
	std::map<int, std::string> textures/*never use on load*/;
#ifdef QT_CORE_LIB
	std::map<int, QImage> texturesImage/*just use on load*/;
#endif
	PointNormalTexture pointNormalTexture                ;
	Triangles triangles                                  ;

    float xMax, yMax, zMax;
    float xMin, yMin, zMin;
private:
	
};
 
class VertexElementCallBack : 
	public ModelLoaderCallBack {
	class ThisPrivate;
public:
	ThisPrivate * thisp = 0;
	~VertexElementCallBack();
	VertexElementCallBack();

	typedef std::uint32_t IndexType;
	class Face {
	public:
		union {
			struct {
				IndexType first;
				IndexType second;
				IndexType third;
			};
			IndexType values[3];
		};
	};
		
	virtual void begin()                               override; 
	virtual void findAFace(FaceType)                   override;
	virtual void findPoint(int, float, float, float)   override;
	virtual void endFindAFace(FaceType)                override;
	virtual void end()                                 override;

bool loadFile(const std::string &) override;
bool saveFile(const std::string &, const std::string & = "")const override;

	std::vector<Point3> points;
	std::vector<Face> triangles;

	float xMax, yMax, zMax;
	float xMin, yMin, zMin;

private:
	Face * currentFace = 0;
};

}


#endif



