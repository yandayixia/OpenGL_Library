#pragma once

#include <gl/glew.h>


namespace MyEngine{
	//Only to be used within Vertex class, wraps the corrdinates
	struct Position{
		float x;
		float y;
	};
	//Only to be used within the Vertex class, wraps the ColorRGBA8 data
	struct ColorRGBA8{
		ColorRGBA8():r(0), g(0), b(0), a(0){}
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :r(R), g(G), b(B), a(A){}
		void SetColor(GLubyte R, GLubyte G, GLubyte B, GLubyte A){
			r = R;
			g = G;
			b = B;
			a = A;
		}
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	//Only to be used within the Vertex class, wraps  the UV coordinate data to be used in the shadders.
	struct UV{
		float u;
		float v;
	};

	struct Vertex {
		Position _position;//8 bytes
		ColorRGBA8 _color;//4 bytes
		//want to make it a multiple of 4.
		
		//uv texture coordinates
		UV _uv;

		//Setter function for _color
		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
			_color.SetColor(r,g,b,a);
		}

		//Setter function for _uv
		void SetUV(float u, float v){
			_uv.u = u;
			_uv.v = v;
		}

		//Setter function for _position
		void SetPosition(float x, float y){
			_position.x = x;
			_position.y = y;
		}
	};
}