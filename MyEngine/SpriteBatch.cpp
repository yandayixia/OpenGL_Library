#include "SpriteBatch.h"

#include <vector>
#include <algorithm>

namespace MyEngine{
	RenderBatch::RenderBatch(GLuint offset, GLuint numVertices, GLuint texture):
	_offset(offset),
	_numVertices(numVertices),
	_texture(texture)
	{
	
	}

	SpriteBatch::SpriteBatch() :_vbo(0), _vao(0){}
	
	SpriteBatch::~SpriteBatch(){}

	void SpriteBatch::CreateRenderBatches(){
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty()){
			return;
		}

		int offset = 0;
		int cv = 0;//current vertex

		//current glyph
		for (int cg = 0; cg < _glyphs.size(); cg++){
			if ((cg == 0) || (_glyphPointers[cg]->_texture != _glyphPointers[cg - 1]->_texture)){
				_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->_texture);
			}
			else{
				_renderBatches.back()._numVertices += 6;
			}
			vertices[cv++] = _glyphPointers[cg]->_topLeft;
			vertices[cv++] = _glyphPointers[cg]->_bottomLeft;
			vertices[cv++] = _glyphPointers[cg]->_bottomRight;
			vertices[cv++] = _glyphPointers[cg]->_bottomRight;
			vertices[cv++] = _glyphPointers[cg]->_topRight;
			vertices[cv++] = _glyphPointers[cg]->_topLeft;
			offset += 6;
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void SpriteBatch::CreateVertexArray(){
		if (_vao == 0){
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);
		if (_vbo == 0){
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//Sending in only 1 array which has index 0.
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//Tell open gl where the data, (which index to start with/
		//								size of the group of data/
		//								the type of array elemetns/
		//								normalize? converte to a range between zero and one./ 
		//								size of stride, the size of your vertex structure/
		//								the offset in bytes, of where the data is in the structure) 
		//this provides the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _position));
		//this is the color atrribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, _color));
		//this provides the postion of uv pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _uv));
		
		glBindVertexArray(0);

	}

	void SpriteBatch::SortGlyphs(){
		switch (_sortType){
			case GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
				break;
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
				break;
			case GlyphSortType::TEXTURE:
				std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
				break;
		}
	}

	void SpriteBatch::Init(){
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType){
		//How we want to sort
		_sortType = sortType;
		_renderBatches.clear();

		_glyphs.clear();
	}

	void SpriteBatch::End(){
		//setup all pointers for fast sorting
		_glyphPointers.resize(_glyphs.size());
		for (int i = 0; i < _glyphs.size(); i++){
			_glyphPointers[i] = &(_glyphs[i]);
		}
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const  glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color){
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}

	bool SpriteBatch::compareBackToFront(Glyph * a, Glyph* b){
		return (a->_depth > b->_depth);
	}

	bool SpriteBatch::compareFrontToBack(Glyph * a, Glyph* b){
		return (a->_depth < b->_depth);
	}

	bool SpriteBatch::compareTexture(Glyph * a, Glyph* b){
		return (a->_texture < b->_texture);
	}

	//Render it to screen
	void SpriteBatch::RenderBatche(){
		glBindVertexArray(_vao);

		for(int i = 0; i < _renderBatches.size(); i++){
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i]._texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i]._offset, _renderBatches[i]._numVertices);
		}

		glBindVertexArray(0);
	}
}