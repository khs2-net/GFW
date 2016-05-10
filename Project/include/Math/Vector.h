#ifndef _HEADER_GFW_MATH_VECTOR_
#define _HEADER_GFW_MATH_VECTOR_
#pragma warning(push)
namespace GFW {
namespace Math {
struct Vertex {
	union {
		struct {
			float x, y, z,w;
		};
		struct {
			float p[4];
		};
	};
	union {
		struct {
			float u, v;
		};
		struct {
			float uv[2];
		};
	};
	union {
		struct {
			float r, g, b,a;
		};
		struct {
			float color[4];
		};
	};
};
}
}

#pragma warning(pop)
#endif