#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
namespace MyEngine{
	enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
	};

	class Glyph{
	public:
		Glyph(){};
		Glyph(const glm::vec4& destRect, const  glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color):
			_texture(texture),
			_depth(depth)
		{
			_topLeft._color = color;
			_topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
			_topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

			_bottomLeft._color = color;
			_bottomLeft.SetPosition(destRect.x, destRect.y);
			_bottomLeft.SetUV(uvRect.x, uvRect.y);

			_bottomRight._color = color;
			_bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
			_bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

			_topRight._color = color;
			_topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			_topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}

		GLuint _texture;
		float _depth;

		Vertex _topLeft;
		Vertex _bottomLeft;
		Vertex _topRight;
		Vertex _bottomRight;

	};	
	
	class RenderBatch{

	public:
		RenderBatch(GLuint offset, GLuint numVertices, GLuint texture);
		GLuint _offset;
		GLuint _numVertices;
		GLuint _texture;
	};

	class SpriteBatch
	{
		GLuint _vbo;
		GLuint _vao;
		//the actual glyphs.
		std::vector<Glyph> _glyphs;
		// this is for sorting
		std::vector<Glyph*> _glyphPointers;


		std::vector<RenderBatch> _renderBatches;
		GlyphSortType _sortType;

		void CreateRenderBatches();
		void CreateVertexArray();
		void SortGlyphs();

		static bool compareFrontToBack(Glyph * a, Glyph* b);
		static bool compareBackToFront(Glyph * a, Glyph* b);
		static bool compareTexture(Glyph * a, Glyph* b);
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();
		void Draw(const glm::vec4& destRect, const  glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
		//Render it to screen
		void RenderBatche();
	};

}