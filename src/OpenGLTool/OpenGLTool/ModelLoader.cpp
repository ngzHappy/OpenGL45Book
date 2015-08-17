#include "ModelLoader.hpp"

/*
本函数仅供测试
*/
#include <map>
#include <list>
#include <vector>
#include <cstdlib>
#include <cstdbool>
#include <ciso646>
#include <string>
#include <cstddef>
#include <fstream>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#ifdef QT_CORE_LIB
#include <QDebug>
#endif

namespace {
/* ----- */
	int apply_material(
		const aiMaterial *mtl,
		gl::ModelLoaderCallBack * ,
		std::map<std::string, int> * texture_
		) {
		int textureID = -1;
		aiString texPath;
			if ( AI_SUCCESS == mtl->GetTexture(
			aiTextureType_DIFFUSE, 0, &texPath)){
			auto fd_ = texture_->find(std::string(texPath.data));
			if (fd_!=texture_->end()) {
				textureID = fd_->second;
			}
			else {
#ifdef QT_CORE_LIB
				qDebug() << ((char *)texPath.data) << "can not found!";
#endif
			}
		}
		return textureID;
	}
/* ----- */
	bool Import3DFromFile(
		const std::string& pFile,
		gl::ModelLoaderCallBack * callBack
		) {
		Assimp::Importer importer;

		union {
			const aiScene* scene;
			const aiScene* sc   ;
		};

		//scene = importer.ReadFile(pFile,
		//	aiProcess_CalcTangentSpace/*后处理标志，自动计算切线和副法线*/|
		//	aiProcess_Triangulate /*后处理标志，自动将四边形面转换为三角面*/|
		//	aiProcess_JoinIdenticalVertices /*后处理标志，自动合并相同的顶点*/|
		//	aiProcess_SortByPType /*后处理标志，将不同图元放置到不同的模型中去，图片类型可能是点、直线、三角形等*/|
		//	0
		//	);  

		scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality );

		//std::unique_ptr<int> s;

		if (scene==0) {
			callBack->error("assimp can not load the file!");
			return false;
		}

		typedef aiNode* NodeType;
		typedef std::list< NodeType > NodeListType;
		NodeListType nodes;
		if (0 == sc->mRootNode) { 
			callBack->error("assimp can not find any data!");
			return false;
		}
		
		std::map<std::string, int> texture_;
		 {
			/*寻找所有texture name ,并给他们编号*/
			std::map<int, std::string> textures;
			for (int m_ = 0; m_<int(scene->mNumMaterials); ++m_) {
				int texIndex = 0;
				aiReturn texFound = AI_SUCCESS;
				aiString path;	// filename
				for (;;) {
					texFound = 
						scene->mMaterials[m_]->\
						GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
					if (texFound == AI_SUCCESS) {
						++texIndex;
						int ts = int(textures.size());
						std::string tn((const char *)( path.data ));
						if (texture_.count(tn)==0) {
							textures[ts] = tn;
							texture_[tn] = ts;
						}
					}
					else {
						break;
					}
				}  ;
			}
			callBack->findTextures(std::move(textures));
		}

		nodes.push_back(sc->mRootNode);
 
		while( nodes.empty()==false ) {
			union { 
				NodeType currentNode; 
				NodeType nd         ;
			};
			currentNode = nodes.front();
			nodes.pop_front();
			if (0 == currentNode) { continue; }

			typedef decltype(currentNode->mNumChildren) NodeNumType;
			/* 开始处理此片段 */
			for (NodeNumType n = 0;n<nd->mNumMeshes;++n){//0

				const struct aiMesh* mesh = 
					scene->mMeshes[nd->mMeshes[n]];
				if (mesh == 0) { continue; }
				
				auto texture0_ID = apply_material(
					sc->mMaterials[mesh->mMaterialIndex],
					callBack,
					&texture_
					);

				//qDebug() << texture0_ID;

				for (NodeNumType t = 0; t < mesh->mNumFaces; ++t) {
					const struct aiFace* face = &mesh->mFaces[t];
					if (face == 0) { continue; }
					if (face->mNumIndices != 3) {
					/*只处理三角形*/
						continue;
					}

					class FindFace{
						gl::ModelLoaderCallBack * cbk;
						gl::ModelLoaderCallBack::FaceType faceType;
					public:
						FindFace(
							gl::ModelLoaderCallBack *v,
							unsigned int ft
							):cbk(v),
							faceType(gl::ModelLoaderCallBack::FaceType(ft)){
							cbk->findAFace( faceType );
						}
						~FindFace() { 
							cbk->endFindAFace(faceType); 
						}
					};

					FindFace __findface( callBack, face->mNumIndices);

					for (
						NodeNumType i_0_ = 0; 
					    i_0_ < face->mNumIndices; 
					    ++i_0_) {
						auto vertexIndex = face->mIndices[i_0_];

						/* 
						texture坐标 
						此函数必须放到最前面
						*/
						{
							/*bool textures_has[3]{
								mesh->HasTextureCoords(0),
								mesh->HasTextureCoords(1),
								mesh->HasTextureCoords(2)
							};
							
							int texture__012 = 
								textures_has[2] ? 2 : (textures_has[1] ? 1 : 0);
								*/
							enum { texture__012=0 };
							if (mesh->HasTextureCoords(texture__012)) {
								const auto & texture =
									mesh->mTextureCoords[texture__012][vertexIndex];
								float u = texture.x;
								float v = texture.y;

								//if (u > 1.0f) { u -= 1; }
								//if (u < 0.0f) { u += 1; }
								//if (v > 1.0f) { v -= 1; }
								//if (v < 0.0f) { v += 1; }

								callBack->findTexture(
									i_0_,
									u  ,
									v  ,
									texture0_ID
									);
							}
						}

						/* 法线 */
						if (mesh->mNormals) {
							const auto & normals = 
								mesh->mNormals[vertexIndex];
							callBack->findNormal(
								i_0_,
								normals.x,
								normals.y,
								normals.z
								);
						}

						/* 顶点坐标 */
						if(mesh->mVertices){
							const auto & vertice = 
								mesh->mVertices[vertexIndex];
							callBack->findPoint(
								i_0_,
								vertice.x,
								vertice.y,
								vertice.z
								);
						}

						/* 顶点颜色 */
						if (mesh->HasVertexColors(0)) {
							const auto & color =
								mesh->mColors[0][vertexIndex];
							callBack->findPointColor(
								i_0_,
								color.r,
								color.g,
								color.b,
								color.a
								);
						}
									

					}/* end a face */

				}

			}//~0
			/* 将子对象加入处理队列 */
			for (NodeNumType n = 0; n < currentNode->mNumChildren; ++n) {
				nodes.push_back(currentNode->mChildren[n]);
			}
		}
		return true;
	}
}

namespace gl {


bool modelLoader(
const std::string & fileName,
ModelLoaderCallBack * callBack
) {
	if (0 == callBack) { 
		return false; 
	}
	if (fileName.empty()) { 
		callBack->error("fileName is null");
		return false; 
	}
	{
		std::ifstream ifs(fileName);
		if (false==ifs.is_open() ) {
			callBack->error(fileName + " can not be opened ");
			return false;
		}
	}
	/************************************/
	return Import3DFromFile(fileName,callBack);
	/************************************/
	return false;
}


}
