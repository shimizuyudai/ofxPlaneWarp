#include "ofxPlane.h"

void ofxPlane::draw(ofTexture & texture)
{
	texture.bind();
	mesh.draw();
	texture.unbind();

}

void ofxPlane::setup(float x, float y, float w, float h, int wSeg, int hSeg)
{
	widthSegment = wSeg;
	heightSegment = hSeg;
	auto startX = x;
	auto startY = y;

	for (auto i = 0; i < hSeg; i++) {
		for (auto j = 0; j < wSeg; j++) {
			auto vertex = ofVec2f(startX + (w / (float)(wSeg -1))*(float)(j), startY + (h / (float)(hSeg - 1))*(float)(i));
			mesh.addVertex(vertex);
			auto uv = ofVec2f((float)j / (float)(wSeg-1), (float)i / (float)(hSeg-1));
			mesh.addTexCoord(uv);
		}
	}

	for (auto i = 0; i < hSeg; i++) {
		for (auto j = 0; j < wSeg; j++) {
			if (j + 1 < wSeg && i + 1 < hSeg) {
				auto index = j + (i*wSeg);
				mesh.addIndex(index);
				mesh.addIndex(index + wSeg);
				mesh.addIndex(index + 1);
				mesh.addIndex(index + 1);
				mesh.addIndex(index + wSeg);
				mesh.addIndex(index + wSeg + 1);
			}
		}
	}
}

ofVec2f ofxPlane::getTopLeft()
{
	return mesh.getVertex(0);
}

ofVec2f ofxPlane::getTopRight()
{
	return mesh.getVertex(widthSegment - 1);
}

ofVec2f ofxPlane::getBottomLeft()
{
	return mesh.getVertex(widthSegment*(heightSegment - 1));
}

ofVec2f ofxPlane::getBottomRight()
{
	return mesh.getVertex((widthSegment*heightSegment) - 1);
}

vector<ofVec3f> ofxPlane::getVertices()
{
	return this->mesh.getVertices();
}

ofMesh & ofxPlane::getMesh()
{
	return this->mesh;
}

void ofxPlane::setVertices(vector<ofVec2f>& vertices)
{
	if (mesh.getNumVertices() != vertices.size())return;
	for (auto i = 0; i < vertices.size(); i++) {
		mesh.setVertex(i,vertices[i]);
	}
}

void ofxPlane::setVertex(int index, ofVec2f vertex)
{
	if (index < 0 || index >= mesh.getNumVertices())return;
	mesh.setVertex(index,vertex);
}

void ofxPlane::drawWireframe()
{
	mesh.drawWireframe();
}
