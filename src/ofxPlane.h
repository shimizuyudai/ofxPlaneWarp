#pragma once

#include "ofMain.h"

class ofxPlane {
public:
	void draw(ofTexture& texture);
	void drawWireframe();
	void setup(float x, float y, float w, float h, int wSeg, int hSeg);
	ofVec2f getTopLeft();
	ofVec2f getTopRight();
	ofVec2f getBottomLeft();
	ofVec2f getBottomRight();
	vector<ofVec2f> getVertices();
	ofMesh& getMesh();
	void setVertices(vector<ofVec2f>& vertices);
	void setVertex(int index,ofVec2f vertex);

protected:

	ofMesh mesh;
	int widthSegment, heightSegment;
};