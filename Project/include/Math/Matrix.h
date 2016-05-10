#ifndef _HEADER_GFW_MATH_MATRIX_
#define _HEADER_GFW_MATH_MATRIX_
#pragma warning(push)

namespace GFW {
namespace Math {

struct Matrix3x3 {
	union {
		struct { float p[9]; };
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
	};
	Matrix3x3 Transpose() {
		Matrix3x3 v;
		for (int i = 0; i < 3; i++) {
			for (int ii = 0; ii < 3; ii++) {
				((float**)v.p)[i][ii] = ((float**)this->p)[ii][i];
			}
		}
	}
};
struct Matrix4x4 {
	union {
		struct { float p[16]; };
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
	};
	Matrix4x4 Transpose() {
		Matrix4x4 v;
		for (int i = 0; i < 4; i++) {
			for (int ii = 0; ii < 4; ii++) {
				((float**)v.p)[i][ii] = ((float**)this->p)[ii][i];
			}
		}
	}
};

}
}

#pragma warning(pop)
#endif