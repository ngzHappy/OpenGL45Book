#ifndef XX_BASE_TYPE__
#define XX_BASE_TYPE__

namespace gl {

	class Float1 {
		float value;
	};

	class Float2 {
	public:
		union {
			struct { float x, y; };
			float values[2];
		};
	};

	typedef Float2 Point2;

	class Float3 {
	public:
		union {
			struct { float x, y, z; };
			float values[3];
		};
	};

	typedef Float3 Point3;

	class Float4 {
	public:
		union {
			struct { float x, y, z,w; };
			float values[4];
		};
	};

	typedef Float4 Point4;

	class Float5 {
	public:
		union {
			float values[5];
		};
	};

	class Float6 {
	public:
		union {
			float values[6];
		};
	};

	class Float7 {
	public:
		union {
			float values[7];
		};
	};

	class Float8 {
	public:
		union {
			float values[8];
		};
	};

	class Float9 {
	public:
		union {
			float values[9];
		};
	};

	class Float10 {
	public:
		union {
			float values[10];
		};
	};

	class Float11 {
	public:
		union {
			float values[11];
		};
	};

	class Float12 {
	public:
		union {
			float values[12];
		};
	};

	class Float13 {
	public:
		union {
			float values[13];
		};
	};

	class Float14 {
	public:
		union {
			float values[14];
		};
	};

	class Float15 {
	public:
		union {
			float values[15];
		};
	};

	class Float16 {
	public:
		union {
			float values[16];
		};
	};

}


#endif
