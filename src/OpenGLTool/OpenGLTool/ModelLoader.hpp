#ifndef _0_Model_LOader__hpp__
#define _0_Model_LOader__hpp__

#include <string>
#include <map>

namespace gl {



class ModelLoaderCallBack {
	/* can not copy or copy create */
	ModelLoaderCallBack(const ModelLoaderCallBack &) {}
	ModelLoaderCallBack(ModelLoaderCallBack &&) {}
	ModelLoaderCallBack & operator=(const ModelLoaderCallBack &) = delete;
	ModelLoaderCallBack & operator=(ModelLoaderCallBack &&) = delete;
public:
	enum FaceType {
		POINTS=1,
		LINES=2,
		TRIANGLES=3,
		POLYGON=4
	};

	ModelLoaderCallBack() {}
	virtual ~ModelLoaderCallBack() {}
	virtual void error(const std::string &) {}

	virtual void findPoint(int,float,float,float) {
	}

	virtual void findNormal(int,float, float, float) {
	}
	
	virtual void findPointColor(int,float,float ,float,float) {}

	virtual void findTexture(int,float, float,int ) {
	}

	virtual void endFindAFace( FaceType ) {}

	virtual void findAFace( FaceType ) {}
	virtual void findTextures(std::map<int,std::string>) {}

	virtual void begin() {}
	virtual void end() {}
	void start() { begin(); }
	void finish() { end(); }

	virtual bool loadFile(const std::string&) { return false; }
	virtual bool saveFile(const std::string&, const std::string & TextureRootPath= "") const {
		return false;
		(void) TextureRootPath;
	}

};

extern bool modelLoader(
	const std::string & fileName,
	ModelLoaderCallBack * callBack
	);


}

#endif
