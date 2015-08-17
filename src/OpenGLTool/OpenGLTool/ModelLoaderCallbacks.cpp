#include "ModelLoaderCallbacks.hpp"
#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <map>
#include <cassert>
#include <list>
#include <forward_list>
#include <mutex>
#include <cstdint>
#include <cstddef>
#include <ciso646>
#include <memory>
#include <new>
#include <utility>
#include <type_traits>
#include <limits>
#include <cfloat>


#ifdef QT_CORE_LIB
#include <QImageReader>
#include <QImage>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include "../QuaZip/quazipfile.h"
#include "../QuaZip/quazip.h"
#include <QDir>
#endif

#ifndef NDEBUG
#include <fstream>
#endif

namespace {
namespace pri_pool {

	template<typename T>
	class allocType
	{
	private:
		typedef boost::pool<boost::default_user_allocator_malloc_free> MallocFreePoolType;
		typedef std::unique_ptr<MallocFreePoolType> MallocFreePoolPointerType;
		typedef std::map<int, MallocFreePoolPointerType> PoolData;
		typedef std::shared_ptr< PoolData > PoolType;

		MallocFreePoolPointerType makeMallocFreePool(const int _N) {
			return std::move(MallocFreePoolPointerType(new MallocFreePoolType(_N)));
		}
		void tryAdd(const int _N) {
			if (pool->count(_N) == 0) {
				pool->operator[](_N) = makeMallocFreePool(_N);
			}
		}
		//typedef std::recursive_mutex MutexType;
		//typedef std::unique_lock< std::recursive_mutex > LockType;

		enum { IsOneByte = (sizeof(T) == 1) };

		typedef typename std::allocator<T>::difference_type _difference_type;
		typedef typename std::allocator<T>::size_type _size_type;

		//type size_type_
		typedef typename std::conditional<
			bool(IsOneByte),
			_size_type,
			typename std::make_signed<_size_type>::type
		>::type size_type_;

		//difference_type_
		typedef typename std::conditional<
			bool(IsOneByte),
			_difference_type,
			typename std::make_signed<_size_type>::type
		>::type difference_type_;
	public:
		/*这个锁是为了tryAdd而添加*/
		//std::shared_ptr<MutexType> mutex;/*!!data*/
										 /**/
		PoolType pool;/*!!data*/

		allocType() :pool(new PoolData)  {/*默认构造函数*/
			tryAdd(sizeof(T));
		}
//#ifndef NDEBUG
//		~allocType() {
//			qDebug() << " private alloc freed! ";
//		}
//#endif
		template<class U>
		allocType(const allocType<U> & o) :
			pool(o.pool)  {/*转型构造函数*/
			tryAdd(sizeof(T));
			tryAdd(sizeof(U));
		}

		/*拷贝构造函数 =default*/

		template <class U>
		struct rebind
		{
			typedef allocType< U > other;
		};
		/*重新定义类型*/
		typedef size_type_ size_type;
		typedef difference_type_ difference_type;
		typedef T value_type;
		typedef value_type * pointer; //!<
		typedef const value_type * const_pointer;
		typedef value_type & reference;
		typedef const value_type & const_reference;
		/*获得地址*/
		static pointer address(reference r) { return &r; }
		static const_pointer address(const_reference s) { return &s; }

		/*默认构造函数*/
		static void construct(const pointer ptr) { new (ptr)T(); }
		/*拷贝构造函数*/
		static void construct(const pointer ptr, const value_type & t) { new (ptr)T(t); }
		/*按值构造*/
		template<class _Objty,
		class... _Types>
			void construct(_Objty *_Ptr, _Types&&... _Args) {
			new(_Ptr)_Objty(std::forward<_Types>(_Args)...);
		}
		/*析构*/
		static void destroy(const pointer ptr) { 
			ptr->~T(); (void)ptr; 
			/*avoid unused variable warning.*/ 
		}

		/*获得最大大小*/
		static size_type max_size() { return (std::numeric_limits<std::size_t>::max)() / sizeof(T); }

		bool operator==(const allocType &) const { return true; }
		bool operator!=(const allocType &) const { return false; }

		pointer allocate(size_type _Count) {/*获得内存*/
			{
				tryAdd(sizeof(T));
			}
			if (_Count==1) {
				return pointer(pool->operator[](sizeof(T))->malloc());
			}
			auto temp = 
				pointer(pool->operator[](sizeof(T))->ordered_malloc(_Count));
			return temp;
		}
		pointer allocate(size_type _Count, const void *) {/*获得内存*/
			return allocate(_Count);
		}
		void deallocate(pointer _Ptr, size_type _Count) {/*释放内存*/
			//if (_Count==1) {
			//	pool->operator[](sizeof(T))->free(_Ptr);
			//}
			//pool->operator[](sizeof(T))->ordered_free(_Ptr, _Count);
			(void)_Ptr;
			(void)_Count;
			/* 析构的时候一次性释放内存 */
		}
	};
}
}

namespace {
	 
	typedef std::int32_t IntFloat;
	static_assert( sizeof(IntFloat)==sizeof(float),"core error!" );
#if 0
	bool less_than_9(const gl::Float9 * l_, const gl::Float9 * r_) {
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return (*l<*r);
	}

	

	bool less_than_7(const gl::Float7 * l_, const gl::Float7 * r_) {
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return (*l<*r);
	}
		
	bool less_than_5(const gl::Float5 * l_, const gl::Float5 * r_) {
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return (*l<*r);
	}

	bool less_than_4(const gl::Float4 * l_, const gl::Float4 * r_) {
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return (*l<*r);
	}
#endif

	bool less_than_8(const gl::Float8 * l_, const gl::Float8 * r_) {
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return (*l<*r);
	}

	bool less_than_6(const gl::Float6 * l_, const gl::Float6 * r_) {
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return (*l<*r);
	}

	bool less_than_3(const gl::Point3 * l_, const gl::Point3 * r_) { 
		auto l = (const IntFloat *)l_;
		auto r = (const IntFloat *)r_;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		if (*l < *r) { return true; }
		if (*r < *l) { return false; }
		++l; ++r;
		return ( *l<*r );
	}
	typedef bool(*KeyCompare3Type)(const gl::Point3 *, const gl::Point3 *);
	typedef bool(*KeyCompare6Type)(const gl::Float6 *, const gl::Float6 *);
	typedef bool(*KeyCompare8Type)(const gl::Float8 *, const gl::Float8 *);
}

namespace gl {
class VertexElementCallBack::ThisPrivate {
public:
	VertexElementCallBack * super;
	std::uint32_t faces_size = 0;
	ThisPrivate(VertexElementCallBack * s):
		super(s) ,
		facePool( sizeof(VertexElementCallBack::Face) ),
		pointsPool( sizeof(Point3) ),
		pointsMap(&less_than_3)
		{}

	~ThisPrivate() {}

	boost::pool<boost::default_user_allocator_malloc_free> facePool;
	boost::pool<boost::default_user_allocator_malloc_free> pointsPool;

	std::list<
		Face,
		pri_pool::allocType< Face >
	> faceDataPool;

	std::map<
		Point3 *,
		VertexElementCallBack::IndexType,
		KeyCompare3Type,
		pri_pool::allocType<
		std::pair<Point3 *, VertexElementCallBack::IndexType>
		>
	> pointsMap;
#ifndef NDEBUG
	bool face_[3];
#endif
};

void VertexElementCallBack::begin() {
	if (0==thisp) {
		thisp = new ThisPrivate(this);
	}
	points.clear();
	triangles.clear();

	xMax = NAN;
	yMax = xMax;
	zMax = xMax;

	xMin = xMax;
	yMin = xMax;
	zMin = xMax;

}

VertexElementCallBack::~VertexElementCallBack() {
	delete thisp;
}

VertexElementCallBack::VertexElementCallBack() {
}

void VertexElementCallBack::findAFace\
(VertexElementCallBack::FaceType face_type ) {
	assert(0== currentFace);
	assert( face_type== VertexElementCallBack::FaceType::TRIANGLES);
	currentFace = 
		(VertexElementCallBack::Face *)thisp->facePool.malloc();
#ifndef NDEBUG
	thisp->face_[0] = false;
	thisp->face_[1] = false;
	thisp->face_[2] = false;
#endif
}

void VertexElementCallBack::findPoint\
(int i, float _x, float _y, float _z) {
	assert( currentFace );
	
	auto currentPoint = (Point3 *)thisp->pointsPool.malloc();
	currentPoint->x = _x;
	currentPoint->y = _y;
	currentPoint->z = _z;
	auto pe_ = thisp->pointsMap.end();
	auto cp_ = thisp->pointsMap.find(currentPoint);
	IndexType index_;

	if (cp_==pe_) {
		//插入一个新点
		index_ = thisp->pointsMap.size();
		thisp->pointsMap[currentPoint] = index_ ;
	}
	else {
		//已经存在点
		index_ = cp_->second;
		thisp->pointsPool.free(currentPoint);
	}

	//将当前点加入face
	(*currentFace).values[i] = index_;
	//更新xyz limit

	if (!(xMax > _x)) { xMax = _x; }
	if (!(yMax > _y)) { yMax = _y; }
	if (!(zMax > _z)) { zMax = _z; }

	if (!(_x > xMin)) { xMin = _x; }
	if (!(_y > yMin)) { yMin = _y; }
	if (!(_z > zMin)) { zMin = _z; }

#ifndef NDEBUG
   thisp->face_[i] = true ;
#endif
}

void VertexElementCallBack::endFindAFace\
(VertexElementCallBack::FaceType) {
	assert(currentFace);
	++(thisp->faces_size);
	thisp->faceDataPool.push_back(*currentFace);


	thisp->facePool.free(currentFace);
	currentFace = 0;
#ifndef NDEBUG
	assert(thisp->face_[0]);
	assert(thisp->face_[1]);
	assert(thisp->face_[2]);
#endif
}

void VertexElementCallBack::end() {
	/* 拷贝数据 */
	{
		auto point_size = thisp->pointsMap.size();
		points.resize(point_size);
		auto mb_ = thisp->pointsMap.cbegin();
		auto me_ = thisp->pointsMap.cend();
		for (; mb_ != me_; ++mb_) {
			points[mb_->second] = *mb_->first;
		}
	}
	{
		triangles.reserve(thisp->faces_size);
		auto b_ = thisp->faceDataPool.begin();
		auto e_ = thisp->faceDataPool.end();
		for (;b_!=e_;++b_) {
			triangles.push_back(*b_);
		}
	}
	triangles.shrink_to_fit();
	points.shrink_to_fit();
	/* 删除临时数据 */
	delete thisp;
	thisp = 0;
	currentFace = 0;
}

bool VertexElementCallBack::loadFile(const std::string & fileName) {
	//QXmlStreamReader
#ifdef QT_CORE_LIB
	QuaZip zip( QString::fromLocal8Bit(fileName.data()) );
	if (zip.open(QuaZip::Mode::mdUnzip) == false) {
		return false;
	}
	std::map<QString, QString> infoFile;
	{
		if (zip.setCurrentFile("info.txt")==false) {
			return false;
		}
		QuaZipFile zFile(&zip);
		if (zFile.open( QIODevice::ReadOnly | QFile::Text)==false) {
			return false;
		}
		QXmlStreamReader reader( &zFile );
		bool has__error = reader.hasError();
		bool at__end = reader.atEnd();
		while ( (!has__error)&&(!at__end) ){
			const auto item_type = reader.readNext();
			if(item_type== QXmlStreamReader::StartElement){
				const QString name__ = reader.name().toString() ;
				if (name__ == "root") { continue; }
				const QString value__ = reader.readElementText();
				infoFile[name__] = value__;
			}
			has__error = reader.hasError();
			at__end = reader.atEnd();
		}//~while
	}

	const auto & file_info = infoFile;
	const auto end_info = file_info.end();

	{//顶点索引空间准备
		auto i = file_info.find("indexSize");
		if (i == end_info) { return false; }
		auto index__size = i->second.toULong();
		this->triangles.clear();
		this->triangles.reserve( index__size/3 );
	}

	{//顶点空间准备
		auto i = file_info.find("vertexSize");
		if (i == end_info) { return false; }
		auto vertex__size = i->second.toULong();
		this->points.clear();
		this->points.reserve(vertex__size);
	}

	{ 
		auto i = file_info.find("zMax");
		if (i == end_info) { return false; }
		zMax = i->second.toFloat();
	}

	{
		auto i = file_info.find("zMin");
		if (i == end_info) { return false; }
		zMin = i->second.toFloat();
	}

	{
		auto i = file_info.find("xMax");
		if (i == end_info) { return false; }
		xMax = i->second.toFloat();
	}

	{
		auto i = file_info.find("xMin");
		if (i == end_info) { return false; }
		xMin = i->second.toFloat();
	}

	{
		auto i = file_info.find("yMax");
		if (i == end_info) { return false; }
		yMax = i->second.toFloat();
	}

	{
		auto i = file_info.find("yMin");
		if (i == end_info) { return false; }
		yMin = i->second.toFloat();
	}

	{//读取索引
		auto i = file_info.find("vertexIndex");
		if (i == end_info) { return false; }
		if (zip.setCurrentFile(i->second) == false) {
			return false;
		}
		QuaZipFile zFile(&zip);
		if (zFile.open(QIODevice::ReadOnly  ) == false) {
			return false;
		}
		QDataStream dStream(&zFile);
		dStream.setVersion(QDataStream::Version::Qt_5_5);
		Face face;
		while ( !dStream.atEnd() ){
			dStream >> face.first;
			dStream >> face.second;
			dStream >> face.third;
			triangles.push_back(face);
		}
	}

	{//读顶点
		auto i = file_info.find("vertexFile");
		if (i == end_info) { return false; }
		if (zip.setCurrentFile(i->second) == false) {
			return false;
		}
		QuaZipFile zFile(&zip);
		if (zFile.open(QIODevice::ReadOnly) == false) {
			return false;
		}
		QDataStream dStream(&zFile);
		dStream.setVersion(QDataStream::Version::Qt_5_5);
		gl::Point3 point;
		while (!dStream.atEnd()) {
			dStream >> point.x;
			dStream >> point.y;
			dStream >> point.z;
			points.push_back(point);
		}
	}

	return true;
#else
	return false;
#endif

}//loadFile//



bool VertexElementCallBack::saveFile(const std::string & fileName, const std::string &) const {
#ifdef QT_CORE_LIB
	QuaZip zip(QString::fromLocal8Bit(fileName.data()));
	if (zip.open(QuaZip::Mode::mdCreate)==false) {
		return false;
	}

	{
		QuaZipFile zFile( &zip );
		QuaZipNewInfo info("info.txt" );
		if ( zFile.open(QIODevice::WriteOnly,info) ) {
			QByteArray all_info(R"(<root>
<vertexFile>vertex</vertexFile>
<vertexIndex>index</vertexIndex>
<vertexSize>)");
			all_info += QString("%1").arg(points.size()) ;
			all_info += "</vertexSize>\n";

			all_info += "<indexSize>";
			all_info += QString("%1").arg(triangles.size()*3);
			all_info += "</indexSize>\n";

			all_info += "<xMax>";
			all_info += QString("%1").arg(xMax);
			all_info += "</xMax>\n";

			all_info += "<yMax>";
			all_info += QString("%1").arg(yMax);
			all_info += "</yMax>\n";

			all_info += "<zMax>";
			all_info += QString("%1").arg(zMax);
			all_info += "</zMax>\n";

			all_info += "<yMin>";
			all_info += QString("%1").arg(yMin);
			all_info += "</yMin>\n";

			all_info += "<zMin>";
			all_info += QString("%1").arg(zMin);
			all_info += "</zMin>\n";

			all_info += "<xMin>";
			all_info += QString("%1").arg(xMin);
			all_info += "</xMin>\n";

			all_info += "</root>";
			zFile.write( all_info );
		}
		else {
			return false;
		}
	}

	{
		QuaZipFile zFile(&zip);
		QuaZipNewInfo info("vertex");
		if (zFile.open(QIODevice::WriteOnly, info)) {
			QDataStream dStream( &zFile );
			dStream.setVersion(QDataStream::Version::Qt_5_5);
			for ( const auto & i:points ) {
				dStream << i.x;
				dStream << i.y;
				dStream << i.z;
			}
		}
		else {
			return false;
		}
	}

	{
		QuaZipFile zFile(&zip);
		QuaZipNewInfo info("index");
		if (zFile.open(QIODevice::WriteOnly, info)) {
			QDataStream dStream(&zFile);
			dStream.setVersion(QDataStream::Version::Qt_5_5);
			auto ri = triangles.begin();
			auto re = triangles.end();
			for (;ri!=re;++ri) {
				dStream << ri->first;
				dStream << ri->second;
				dStream << ri->third;
			}
		}
		else {
			return false;
		}

		
}
	return true;
	 
#else
	return false;
#endif
}/*saveFile**********************************/
	 
	
}//gl


namespace gl {
class VertexNormalElementCallBack::ThisPrivate {
public:
#ifndef NDEBUG
	bool face_p[3];
	bool face_n[3];
#endif
	typedef gl::Float6 FaceDataType ;
	FaceDataType* face_points[3]  ;
 
	std::map<
		gl::Float6 *,
		VertexElementCallBack::IndexType,
		KeyCompare6Type,
		pri_pool::allocType<
		std::pair<gl::Float6 *, VertexElementCallBack::IndexType>
		>
	> pointsMap;

	std::list<
		Face,
		pri_pool::allocType< Face >
	> faceDataPool;


	boost::pool<boost::default_user_allocator_malloc_free> pointsPool;
	ThisPrivate() :
		pointsPool(sizeof(gl::Float6 )),
		pointsMap(&less_than_6)
		{}
};

VertexNormalElementCallBack::VertexNormalElementCallBack() {
}
VertexNormalElementCallBack::~VertexNormalElementCallBack() {
	delete thisp;
}

void VertexNormalElementCallBack::begin() {
	assert(thisp==0);
	thisp = new ThisPrivate;
 
	xMax = NAN;
	yMax = xMax;
	zMax = xMax;

	xMin = xMax;
	yMin = xMax;
	zMin = xMax;

	thisp->face_points[0] = 0;
	thisp->face_points[1] = 0;
	thisp->face_points[2] = 0;
}
void VertexNormalElementCallBack::end() {
	assert(thisp);
	
	{
		triangles.clear();
		auto face__size = thisp->faceDataPool.size();
		triangles.reserve( face__size );
		for (const auto & i:thisp->faceDataPool) {
			triangles.push_back( i);
		}
	}

	{
		pointNormal.clear();
		pointNormal.resize(thisp->pointsMap.size());
		for ( const auto & i:thisp->pointsMap ) {
			pointNormal[i.second] = *(i.first);
		}
	}

	delete thisp;
	thisp = 0;
}
void VertexNormalElementCallBack::findAFace(FaceType) {
#ifndef NDEBUG
	for (bool & i : thisp->face_p) { i = false; }
	for (bool & i : thisp->face_n) { i = false; }
#endif
	assert(thisp->face_points[0] == 0);
	assert(thisp->face_points[1] == 0);
	assert(thisp->face_points[2] == 0);

	thisp->face_points[0] = 
		(ThisPrivate::FaceDataType *)thisp->pointsPool.malloc();
	thisp->face_points[1] =
		(ThisPrivate::FaceDataType *)thisp->pointsPool.malloc();
	thisp->face_points[2] =
		(ThisPrivate::FaceDataType *)thisp->pointsPool.malloc();

}
void VertexNormalElementCallBack::findPoint(
	int i, float _x, float _y, float _z) {
#ifndef NDEBUG
	thisp->face_p[i] = true;
#endif
	auto & pn = *((thisp->face_points)[i]);
	pn.values[0] = _x;
	pn.values[1] = _y;
	pn.values[2] = _z;

	if (!(xMax > _x)) { xMax = _x; }
	if (!(yMax > _y)) { yMax = _y; }
	if (!(zMax > _z)) { zMax = _z; }

	if (!(_x > xMin)) { xMin = _x; }
	if (!(_y > yMin)) { yMin = _y; }
	if (!(_z > zMin)) { zMin = _z; }

}

void VertexNormalElementCallBack::findNormal(
	int i, float nx, float ny, float nz) {
#ifndef NDEBUG
	thisp->face_n[i] = true;
#endif
	auto & pn =*((thisp->face_points)[i]);
	pn.values[3] = nx;
	pn.values[4] = ny;
	pn.values[5] = nz;
	
}

void VertexNormalElementCallBack::endFindAFace(FaceType) {
#ifndef NDEBUG
	for (bool & i : thisp->face_p) { assert( i ) ; }
	for (bool & i : thisp->face_n) { assert( i ) ; }
#endif

	Face face;

	{
		enum {__I=0};
		auto end_ = thisp->pointsMap.end();
		auto i_= thisp->pointsMap.find(thisp->face_points[__I]);
		if (i_==end_) {
			auto ps_ = thisp->pointsMap.size();
			thisp->pointsMap[thisp->face_points[__I]] = ps_;
			face.first = ps_;
		 
		}
		else {
			face.first = i_->second ;
			thisp->pointsPool.free(thisp->face_points[__I]);
		}
	}

	{
		enum { __I = 1 };
		auto end_ = thisp->pointsMap.end();
		auto i_ = thisp->pointsMap.find(thisp->face_points[__I]);
		if (i_ == end_) {
			auto ps_ = thisp->pointsMap.size();
			thisp->pointsMap[thisp->face_points[__I]] = ps_;
			face.second = ps_;
	 
		}
		else {
			face.second = i_->second;
			thisp->pointsPool.free(thisp->face_points[__I]);
		}
	}

	{
		enum { __I = 2 };
		auto end_ = thisp->pointsMap.end();
		auto i_ = thisp->pointsMap.find(thisp->face_points[__I]);
		if (i_ == end_) {
			auto ps_ = thisp->pointsMap.size();
			thisp->pointsMap[thisp->face_points[__I]] = ps_;
			face.third = ps_;
 
		}
		else {
			face.third = i_->second;
			thisp->pointsPool.free(thisp->face_points[__I]);
		}
	}

	thisp->face_points[0] = 0;
	thisp->face_points[1] = 0;
	thisp->face_points[2] = 0;
	 
	thisp->faceDataPool.push_back(face);
}

bool VertexNormalElementCallBack::loadFile(
	const std::string & fileName) {
#ifdef QT_CORE_LIB
	QuaZip zip(QString::fromLocal8Bit(fileName.data()));
	if (zip.open(QuaZip::Mode::mdUnzip) == false) {
		return false;
	}

	std::map<QString, QString> infoFile;
	{
		if (zip.setCurrentFile("info.txt") == false) {
			return false;
		}
		QuaZipFile zFile(&zip);
		if (zFile.open(QIODevice::ReadOnly | QFile::Text) == false) {
			return false;
		}
		QXmlStreamReader reader(&zFile);
		bool has__error = reader.hasError();
		bool at__end = reader.atEnd();
		while ((!has__error) && (!at__end)) {
			const auto item_type = reader.readNext();
			if (item_type == QXmlStreamReader::StartElement) {
				const QString name__ = reader.name().toString();
				if (name__ == "root") { continue; }
				const QString value__ = reader.readElementText();
				infoFile[name__] = value__;
			}
			has__error = reader.hasError();
			at__end = reader.atEnd();
		}//~while
	}

	const auto & file_info = infoFile;
	const auto end_info = file_info.end();

	{//顶点索引空间准备
		auto i = file_info.find("indexSize");
		if (i == end_info) { return false; }
		auto index__size = i->second.toULong();
		this->triangles.clear();
		this->triangles.reserve(index__size / 3);
	}

	{//顶点空间准备
		auto i = file_info.find("vertexSize");
		if (i == end_info) { return false; }
		auto vertex__size = i->second.toULong();
		this->pointNormal.clear();
		this->pointNormal.reserve(vertex__size);
	}

	{
		auto i = file_info.find("zMax");
		if (i == end_info) { return false; }
		zMax = i->second.toFloat();
	}

	{
		auto i = file_info.find("zMin");
		if (i == end_info) { return false; }
		zMin = i->second.toFloat();
	}

	{
		auto i = file_info.find("xMax");
		if (i == end_info) { return false; }
		xMax = i->second.toFloat();
	}

	{
		auto i = file_info.find("xMin");
		if (i == end_info) { return false; }
		xMin = i->second.toFloat();
	}

	{
		auto i = file_info.find("yMax");
		if (i == end_info) { return false; }
		yMax = i->second.toFloat();
	}

	{
		auto i = file_info.find("yMin");
		if (i == end_info) { return false; }
		yMin = i->second.toFloat();
	}

	{//读取索引
		auto i = file_info.find("vertexIndex");
		if (i == end_info) { return false; }
		if (zip.setCurrentFile(i->second) == false) {
			return false;
		}
		QuaZipFile zFile(&zip);
		if (zFile.open(QIODevice::ReadOnly) == false) {
			return false;
		}
		QDataStream dStream(&zFile);
		dStream.setVersion(QDataStream::Version::Qt_5_5);
		Face face;
		while (!dStream.atEnd()) {
			dStream >> face.first;
			dStream >> face.second;
			dStream >> face.third;
			triangles.push_back(face);
		}
	}

	{//读顶点
		auto i = file_info.find("vertexFile");
		if (i == end_info) { return false; }
		if (zip.setCurrentFile(i->second) == false) {
			return false;
		}
		QuaZipFile zFile(&zip);
		if (zFile.open(QIODevice::ReadOnly) == false) {
			return false;
		}
		QDataStream dStream(&zFile);
		dStream.setVersion(QDataStream::Version::Qt_5_5);
		gl::Float6 point;
		while (!dStream.atEnd()) {
			dStream >> point.values[0];
			dStream >> point.values[1];
			dStream >> point.values[2];
			dStream >> point.values[3];
			dStream >> point.values[4];
			dStream >> point.values[5];
			pointNormal.push_back(point);
		}
	}

	return true;
#else
	return false;
#endif
}
bool VertexNormalElementCallBack::saveFile(
	const std::string & fileName, const std::string &)const {
#ifdef QT_CORE_LIB
	QuaZip zip(QString::fromLocal8Bit(fileName.data()));
	if (zip.open(QuaZip::Mode::mdCreate) == false) {
		return false;
}

	{
		QuaZipFile zFile(&zip);
		QuaZipNewInfo info("info.txt");
		if (zFile.open(QIODevice::WriteOnly, info)) {
			QByteArray all_info(R"(<root>
<vertexFile>vertex</vertexFile>
<vertexIndex>index</vertexIndex>
<vertexSize>)");
			all_info += QString("%1").arg(pointNormal.size());
			all_info += "</vertexSize>\n";

			all_info += "<indexSize>";
			all_info += QString("%1").arg(triangles.size() * 3);
			all_info += "</indexSize>\n";

			all_info += "<xMax>";
			all_info += QString("%1").arg(xMax);
			all_info += "</xMax>\n";

			all_info += "<yMax>";
			all_info += QString("%1").arg(yMax);
			all_info += "</yMax>\n";

			all_info += "<zMax>";
			all_info += QString("%1").arg(zMax);
			all_info += "</zMax>\n";

			all_info += "<yMin>";
			all_info += QString("%1").arg(yMin);
			all_info += "</yMin>\n";

			all_info += "<zMin>";
			all_info += QString("%1").arg(zMin);
			all_info += "</zMin>\n";

			all_info += "<xMin>";
			all_info += QString("%1").arg(xMin);
			all_info += "</xMin>\n";

			all_info += "</root>";
			zFile.write(all_info);
		}
		else {
			return false;
		}
	}

	{
		QuaZipFile zFile(&zip);
		QuaZipNewInfo info("vertex");
		if (zFile.open(QIODevice::WriteOnly, info)) {
			QDataStream dStream(&zFile);
			dStream.setVersion(QDataStream::Version::Qt_5_5);
			for (const auto & i : pointNormal) {
				dStream << i.values[0];
				dStream << i.values[1];
				dStream << i.values[2];
				dStream << i.values[3];
				dStream << i.values[4];
				dStream << i.values[5];
			}
		}
		else {
			return false;
		}
	}

	{
		QuaZipFile zFile(&zip);
		QuaZipNewInfo info("index");
		if (zFile.open(QIODevice::WriteOnly, info)) {
			QDataStream dStream(&zFile);
			dStream.setVersion(QDataStream::Version::Qt_5_5);
			auto ri = triangles.begin();
			auto re = triangles.end();
			for (; ri != re; ++ri) {
				dStream << ri->first;
				dStream << ri->second;
				dStream << ri->third;
			}
		}
		else {
			return false;
		}


	}
	return true;

#else
	return false;
#endif
}

}

namespace gl {

class VertexTextureNormalElementCallBack::ThisPrivate {
	public:
		int texture_size ;
		int current_texture;
		typedef gl::Float8 FaceDataType;
		FaceDataType * current_face_points[3];
#ifndef NDEBUG
		bool v_[3];
		bool n_[3];
		bool t_[3];
#endif
		typedef  std::map<
			gl::Float8 *,
			VertexElementCallBack::IndexType,
			KeyCompare8Type,
			pri_pool::allocType<
			std::pair<gl::Float8 *, VertexElementCallBack::IndexType>
			>
		> PointsMapItemParent;

		class PointsMapItem : public  PointsMapItemParent {
		public:
			PointsMapItem() :PointsMapItemParent(&less_than_8){}
		};

		std::map<int,PointsMapItem>pointsMap;

		std::map<int, std::list<
			Face,
			pri_pool::allocType< Face >
		>
		> faceDataPool;


		boost::pool<
			boost::default_user_allocator_malloc_free
		> pointsPool;

		ThisPrivate() :
			pointsPool(sizeof(gl::Float8)),
			pointsMap()
		{}
};

VertexTextureNormalElementCallBack::\
VertexTextureNormalElementCallBack(){

}

VertexTextureNormalElementCallBack::\
~VertexTextureNormalElementCallBack(){
	delete thisp;
}

void VertexTextureNormalElementCallBack::\
begin(){
	assert(0==thisp);
	thisp = new ThisPrivate;
	thisp->texture_size = 0;
	thisp->current_face_points[1] = 0;
	thisp->current_face_points[0] = 0;
	thisp->current_face_points[2] = 0;

	xMax = NAN;
	yMax = xMax;
	zMax = xMax;

	xMin = xMax;
	yMin = xMax;
	zMin = xMax;
}

void VertexTextureNormalElementCallBack::\
findAFace(FaceType){
	if (thisp->texture_size <= 0) { return; }
	thisp->current_texture = -1;
#ifndef NDEBUG
	thisp->v_[0] = false; thisp->v_[1] = false; thisp->v_[2] = false;
	thisp->n_[0] = false; thisp->n_[1] = false; thisp->n_[2] = false;
	thisp->t_[0] = false; thisp->t_[1] = false; thisp->t_[2] = false;
#endif
	assert( thisp->current_face_points[2] == 0);
	assert( thisp->current_face_points[1] == 0);
	assert( thisp->current_face_points[0] == 0);

	thisp->current_face_points[0] = (gl::Float8 *)thisp->pointsPool.malloc();
	thisp->current_face_points[1] = (gl::Float8 *)thisp->pointsPool.malloc();
	thisp->current_face_points[2] = (gl::Float8 *)thisp->pointsPool.malloc();
}

void VertexTextureNormalElementCallBack::\
findPoint(int i, float _x, float _y, float _z){
	if (thisp->texture_size <= 0) { return; }
	auto & vnt = *(thisp->current_face_points[i]);
	vnt.values[0] = _x;
	vnt.values[1] = _y;
	vnt.values[2] = _z;
#ifndef NDEBUG
	thisp->v_[i] = true;
#endif
	if (!(xMax > _x)) { xMax = _x; }
	if (!(yMax > _y)) { yMax = _y; }
	if (!(zMax > _z)) { zMax = _z; }

	if (!(_x > xMin)) { xMin = _x; }
	if (!(_y > yMin)) { yMin = _y; }
	if (!(_z > zMin)) { zMin = _z; }
}

void VertexTextureNormalElementCallBack::\
findNormal(int i, float dx_, float dy_, float dz_){
	if (thisp->texture_size <= 0) { return; }
	auto & vnt = *(thisp->current_face_points[i]);
	vnt.values[3] = dx_;
	vnt.values[4] = dy_;
	vnt.values[5] = dz_;
#ifndef NDEBUG
	thisp->n_[i] = true;
#endif
}

void VertexTextureNormalElementCallBack::\
endFindAFace(FaceType){
	if (thisp->texture_size <= 0) { return; }
#ifndef NDEBUG
	assert(thisp->v_[0]); assert(thisp->v_[1]); assert(thisp->v_[2]);
	assert(thisp->n_[0]); assert(thisp->n_[1]); assert(thisp->n_[2]);
	assert(thisp->t_[0]); assert(thisp->t_[1]); assert(thisp->t_[2]);
#endif
	Face face;
	auto & current_point_map = thisp->pointsMap[ thisp->current_texture ];
	{
		enum { __I = 0 };
		auto end_ = current_point_map.end();
		auto i_ = current_point_map.find(thisp->current_face_points[__I]);
		if (i_ == end_) {
			auto ps_ = current_point_map.size();
			current_point_map[ thisp->current_face_points[__I] ] = ps_;
			face.first = ps_;
		}
		else {
			face.first = i_->second;
			thisp->pointsPool.free(thisp->current_face_points[__I]);
		}
	}
	{
		enum { __I = 1 };
		auto end_ = current_point_map.end();
		auto i_ = current_point_map.find(thisp->current_face_points[__I]);
		if (i_ == end_) {
			auto ps_ = current_point_map.size();
			current_point_map[thisp->current_face_points[__I]] = ps_;
			face.second = ps_;
		}
		else {
			face.second = i_->second;
			thisp->pointsPool.free(thisp->current_face_points[__I]);
		}
	}
	{
		enum { __I = 2 };
		auto end_ = current_point_map.end();
		auto i_ = current_point_map.find(thisp->current_face_points[__I]);
		if (i_ == end_) {
			auto ps_ = current_point_map.size();
			current_point_map[thisp->current_face_points[__I]] = ps_;
			face.third = ps_;
		}
		else {
			face.third = i_->second;
			thisp->pointsPool.free(thisp->current_face_points[__I]);
		}
	}
	thisp->current_face_points[0] = 0;
	thisp->current_face_points[1] = 0;
	thisp->current_face_points[2] = 0;
	thisp->faceDataPool[thisp->current_texture].push_back(face);
}

void VertexTextureNormalElementCallBack::\
end(){
	assert(thisp);

	{
		triangles.clear();
		for (const auto & i:thisp->faceDataPool ) {
			auto & ctris = triangles[ i.first ];
			ctris.reserve(i.second.size());
			for (const auto & j:i.second) {
				ctris.push_back( j );
			}
		}
	}

	{
		pointNormalTexture.clear();
		for (const auto & i:thisp->pointsMap) {
			auto & d_ = pointNormalTexture[i.first];
			d_.resize( i.second.size() );
			for (const auto & j:i.second) {
				d_[j.second] = *(j.first);
			}
		}
	}

#ifdef QT_CORE_LIB
	texturesImage.clear();
#endif
	
/*
删除所有中间数据
*/
	delete thisp;
	thisp = 0;
}

bool VertexTextureNormalElementCallBack::\
loadFile(const std::string & _fileName ){
	textures.clear();
	texturesImage.clear();
	pointNormalTexture.clear();
	triangles.clear();
#ifdef QT_CORE_LIB
	const QString fileName = QString::fromLocal8Bit( _fileName.data(),_fileName.size() );
	QuaZip zip( fileName );
	if (zip.open(QuaZip::Mode::mdUnzip) == false) {return false;}

	if (zip.setCurrentFile("info.txt") == false) {
		return false;
	}

	class ReaderTexturePack {
	public:
		std::map<QString, QString> infoFile;
	};
	std::list<ReaderTexturePack> readerTexturePacks ;
	auto getPack = [this](QXmlStreamReader * r__) ->ReaderTexturePack {
		ReaderTexturePack ans;
		auto & infoFile = ans.infoFile;
		auto & reader = *r__;
		bool has__error = reader.hasError();
		bool at__end = reader.atEnd();
		while ((!has__error) && (!at__end)) {
			const auto item_type = reader.readNext();
			if (item_type == QXmlStreamReader::StartElement) {
				const QString name__ = reader.name().toString();
				const QString value__ = reader.readElementText();
				infoFile[name__] = value__;
			}
			else {
				if (item_type == QXmlStreamReader::EndElement) {
					const QString name__ = reader.name().toString();
					if (name__ == "Texture") { 
						at__end = true;
						break; }
				}
			}
			has__error = reader.hasError();
			at__end = reader.atEnd();
		}//~while
		return std::move(ans);
	};

	{
		QuaZipFile zFile(&zip);
		if (zFile.open(QIODevice::ReadOnly | QFile::Text) == false) {
			return false;
		}
		QXmlStreamReader reader(&zFile);
		bool has__error = reader.hasError();
		bool at__end = reader.atEnd();
		std::map<QString, QString> infoFile;
		while ((!has__error) && (!at__end)) {
			const auto item_type = reader.readNext();
			if (item_type == QXmlStreamReader::StartElement) {
				const QString name__ = reader.name().toString();
				if (name__ == "root") { continue; }
				if (name__ == "Texture") {
					readerTexturePacks.push_back( std::move( getPack(&reader) ) );
				}else{	
					const QString value__ = reader.readElementText();
					infoFile[name__] = value__;
				}
			}
			has__error = reader.hasError();
			at__end = reader.atEnd();
		}//~while

		const auto & file_info = infoFile;
		auto end_info = file_info.end();
		{
			auto i = file_info.find("zMax");
			if (i == end_info) { return false; }
			zMax = i->second.toFloat();
		}

		{
			auto i = file_info.find("zMin");
			if (i == end_info) { return false; }
			zMin = i->second.toFloat();
		}

		{
			auto i = file_info.find("xMax");
			if (i == end_info) { return false; }
			xMax = i->second.toFloat();
		}

		{
			auto i = file_info.find("xMin");
			if (i == end_info) { return false; }
			xMin = i->second.toFloat();
		}

		{
			auto i = file_info.find("yMax");
			if (i == end_info) { return false; }
			yMax = i->second.toFloat();
		}

		{
			auto i = file_info.find("yMin");
			if (i == end_info) { return false; }
			yMin = i->second.toFloat();
		}

	}
	
	if (readerTexturePacks.empty()) { return false; }
	int currentTexture = 0;
	for (const auto & i: readerTexturePacks) {
		
		const auto & fileInfo = i.infoFile;
		VertexTextureNormalElementCallBack::IndexType indexSize;
		VertexTextureNormalElementCallBack::IndexType vertexSize;
		auto itn = fileInfo.find("TextureName");
		auto ivf = fileInfo.find("vertexFile");
		auto ivi = fileInfo.find("vertexIndex");
		auto ivs = fileInfo.find("vertexSize");
		auto iis = fileInfo.find("indexSize");

		auto e = fileInfo.end();
		if(itn==e){return false;}
		if(ivf==e){return false;}
		if(ivi==e){return false;}
		if(ivs==e){return false;}
		if(iis==e){return false;}

		const auto & vertexFile = ivf->second;
		const auto & vertexIndex = ivi->second;
		const auto & textureName = itn->second;
		indexSize =  iis->second.toUInt();
		vertexSize = ivs->second.toUInt();

		auto & triangles = this->triangles[currentTexture];
		auto & dataofpnt = this->pointNormalTexture[currentTexture];
		this->textures[currentTexture] = textureName.toStdString();

		triangles.reserve(indexSize/3);
		dataofpnt.reserve(vertexSize);

		if (zip.setCurrentFile(textureName) == false) { return false; }
		else {
			QuaZipFile zFile(&zip);
			zFile.open( QFile::ReadOnly );
			QImageReader imageReader(&zFile);
			texturesImage[currentTexture] = imageReader.read();
		}

		if (zip.setCurrentFile(vertexIndex) == false) { return false; } else{
			QuaZipFile zFile(&zip);
			zFile.open(QFile::ReadOnly);
			QDataStream dStream(&zFile);
			dStream.setVersion(QDataStream::Version::Qt_5_5);
			Face face;
			while (!dStream.atEnd()) {
				dStream >> face.first;
				dStream >> face.second;
				dStream >> face.third;
				triangles.push_back(face);
			}
		}

		if (zip.setCurrentFile(vertexFile) == false) { return false; }else {
			QuaZipFile zFile(&zip);
			zFile.open(QFile::ReadOnly);
			QDataStream dStream(&zFile);
			dStream.setVersion(QDataStream::Version::Qt_5_5);
			gl::Float8 point;
			while (!dStream.atEnd()) {
				dStream >> point.values[0];
				dStream >> point.values[1];
				dStream >> point.values[2];
				dStream >> point.values[3];
				dStream >> point.values[4];
				dStream >> point.values[5];
				dStream >> point.values[6];
				dStream >> point.values[7];
				dataofpnt.push_back(point);
			}
		}

		++currentTexture;
	}

	return true;
#else
    return false;
#endif
}

bool VertexTextureNormalElementCallBack::\
saveFile( 
	const std::string & fileName, 
	const std::string & textureRootPath ) const {
 
#ifdef QT_CORE_LIB
	{//1
		QuaZip zip(QString::fromLocal8Bit(fileName.data()));
		if (zip.open(QuaZip::Mode::mdCreate) == false) { return false; }

		{//2
			QuaZipFile zFile(&zip);
			QuaZipNewInfo info("info.txt");
			if (zFile.open(QIODevice::WriteOnly, info)) {
				QByteArray all_info("<root>\n");

				all_info += "<textureSize>";
				all_info += QString("%1").arg(textures.size());
				all_info += "</textureSize>\n";

				all_info += "<xMax>";
				all_info += QString("%1").arg(xMax);
				all_info += "</xMax>\n";

				all_info += "<yMax>";
				all_info += QString("%1").arg(yMax);
				all_info += "</yMax>\n";

				all_info += "<zMax>";
				all_info += QString("%1").arg(zMax);
				all_info += "</zMax>\n";

				all_info += "<yMin>";
				all_info += QString("%1").arg(yMin);
				all_info += "</yMin>\n";

				all_info += "<zMin>";
				all_info += QString("%1").arg(zMin);
				all_info += "</zMin>\n";

				all_info += "<xMin>";
				all_info += QString("%1").arg(xMin);
				all_info += "</xMin>\n";

				/*   */
				for (const auto & i : this->textures) {
					int current_index = i.first;
					if (pointNormalTexture.count(current_index) == 0) { continue; }
					if (triangles.count(current_index) == 0) { continue; }
					const auto & currentPNT = pointNormalTexture.find(current_index)->second;
					const auto & currentFace = triangles.find(current_index)->second;
					all_info += "<Texture>\n";
					all_info += "<TextureName>";
					{
						QString fileName_ = QString::fromStdString(i.second);
						if (fileName_.startsWith(".\\")
							|| fileName_.startsWith("./")
							) {
							fileName_ = fileName_.mid(2);
						}
						all_info += fileName_ ;
					}
					all_info += "</TextureName>\n";
					all_info += "<vertexFile>";
					all_info += QString("%1").arg(current_index) + "vertex";
					all_info += "</vertexFile>\n";
					all_info += "<vertexIndex>";
					all_info += QString("%1").arg(current_index) + "index";
					all_info += "</vertexIndex>\n";
					all_info += "<vertexSize>";
					all_info += QString("%1").arg(currentPNT.size());
					all_info += "</vertexSize>\n";
					all_info += "<indexSize>";
					all_info += QString("%1").arg(currentFace.size() * 3);
					all_info += "</indexSize>\n";
					all_info += "</Texture>";
				}

				all_info += "</root>";
				zFile.write(all_info);
			}
			else {
				return false;
			}
		}//2

		for (const auto & i : this->textures) {//3
			int current_index = i.first;
			if (pointNormalTexture.count(current_index) == 0) { continue; }
			if (triangles.count(current_index) == 0) { continue; }
			const auto & currentPNT = pointNormalTexture.find(current_index)->second;
			const auto & currentFace = triangles.find(current_index)->second;

			{
				QuaZipFile zFile(&zip);
				QuaZipNewInfo info(QString("%1").arg(current_index) + "vertex");
				if (zFile.open(QIODevice::WriteOnly, info)) {
					QDataStream dStream(&zFile);
					dStream.setVersion(QDataStream::Version::Qt_5_5);
					for (const auto & i : currentPNT) {
						dStream << i.values[0];
						dStream << i.values[1];
						dStream << i.values[2];
						dStream << i.values[3];
						dStream << i.values[4];
						dStream << i.values[5];
						dStream << i.values[6];
						dStream << i.values[7];
					}
				}
				else {
					return false;
				}
			}

			{
				QuaZipFile zFile(&zip);
				QuaZipNewInfo info(QString("%1").arg(current_index) + "index");
				if (zFile.open(QIODevice::WriteOnly, info)) {
					QDataStream dStream(&zFile);
					dStream.setVersion(QDataStream::Version::Qt_5_5);
					auto ri = currentFace.begin();
					auto re = currentFace.end();
					for (; ri != re; ++ri) {
						dStream << ri->first;
						dStream << ri->second;
						dStream << ri->third;
					}
				}
				else {
					return false;
				}
			}

			{
				QuaZipFile zFile(&zip);
				QString fileName_ = QString::fromStdString(i.second);
				if (fileName_.startsWith(".\\")
					|| fileName_.startsWith("./")
					) {
					fileName_ = fileName_.mid(2);
				}
				QuaZipNewInfo info(fileName_);
				if (zFile.open(QIODevice::WriteOnly, info)) {
					QDir dir_( QString::fromLocal8Bit(textureRootPath.data()) );
					QString filePath__ = dir_.filePath(QString::fromLocal8Bit(i.second.data()));
					filePath__ = dir_.cleanPath(filePath__);
					QFile file_(filePath__);
					if (file_.open(QIODevice::ReadOnly)) {
						zFile.write(file_.readAll());
					}
					else {
						qDebug() 
							<<  "texture "\
							<<((const char *)(textureRootPath + i.second).data())\
							<< "can not be found!!";
					}
				}
			}

		}//3

}//1
return true;
#else
		return false;
#endif

	
}


void VertexTextureNormalElementCallBack::\
findTextures(std::map<int, std::string> tnames) {
	this->textures = std::move( tnames );
	thisp->texture_size = int(this->textures.size());
}

 //std::ofstream  * ss;
void VertexTextureNormalElementCallBack::\
findTexture(int i, float u, float v, int textureIndex )  {
	if ( thisp->texture_size <= textureIndex ) { 
		qDebug() << "texture error!!";
		return; 
	}
#ifndef NDEBUG
	if ((thisp->t_[0] == false) &&
		(thisp->t_[2] == false) &&
		(thisp->t_[1] == false)  
		) {
assert((thisp->current_texture == -1));
	}
	
#endif
	//if (ss == 0) { ss = new std::ofstream("xxx.txt"); }
	thisp->current_texture = textureIndex;
	assert(textureIndex >= 0);
	auto & vnt = *(thisp->current_face_points[i]);
	vnt.values[6] = u;
	vnt.values[7] = v;

	//*(ss) << u << " " << 
	//	v << " " << textureIndex 
	//	<<" "<< i<< std::endl;;

#ifndef NDEBUG
	thisp->t_[i] = true;
#endif
}

}


/***
中文编码测试
***/


