#include "ofxPlaneWarp.h"

void ofxPlaneWarp::draw(ofTexture & texture)
{
	texture.bind();
	mesh.draw();
	texture.unbind();
	if (isWarpMode) {
		ofSetColor(0, 255, 0, 127);
		for (auto i = 0; i < cornerPoints.size(); i++) {
			ofDrawCircle(cornerPoints[i][0], cornerPoints[i][1], touchDistThreashold);
		}

		ofSetColor(255,0,0);
	}

}

void ofxPlaneWarp::setup(float x, float y, float w, float h, int wSeg, int hSeg)
{
	auto startX = x;
	auto startY = y;

	for (auto i = 0; i < hSeg; i++) {
		for (auto j = 0; j < wSeg; j++) {
			auto vertex = ofVec2f(startX + (w / (float)(wSeg - 1))*(float)(j), startY + (h / (float)(hSeg - 1))*(float)(i));
			mesh.addVertex(vertex);
			basePoints.push_back(cv::Vec2f(vertex.x, vertex.y));
			auto uv = ofVec2f((float)j / (float)wSeg, (float)i / (float)hSeg);
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

	baseCornerPoints.push_back(cv::Vec2f(mesh.getVertex(0).x, mesh.getVertex(0).y));
	baseCornerPoints.push_back(cv::Vec2f(mesh.getVertex(wSeg*(hSeg - 1)).x, mesh.getVertex(wSeg*(hSeg - 1)).y));
	baseCornerPoints.push_back(cv::Vec2f(mesh.getVertex((wSeg*hSeg) - 1).x, mesh.getVertex((wSeg*hSeg) - 1).y));
	baseCornerPoints.push_back(cv::Vec2f(mesh.getVertex(wSeg - 1).x, mesh.getVertex(wSeg - 1).y));

	cornerPoints.push_back(cv::Vec2f(mesh.getVertex(0).x, mesh.getVertex(0).y));
	cornerPoints.push_back(cv::Vec2f(mesh.getVertex(wSeg*(hSeg - 1)).x, mesh.getVertex(wSeg*(hSeg - 1)).y));
	cornerPoints.push_back(cv::Vec2f(mesh.getVertex((wSeg*hSeg) - 1).x, mesh.getVertex((wSeg*hSeg) - 1).y));
	cornerPoints.push_back(cv::Vec2f(mesh.getVertex(wSeg - 1).x, mesh.getVertex(wSeg - 1).y));
}

void ofxPlaneWarp::update()
{
	h = cv::findHomography(baseCornerPoints, cornerPoints);
	vector<cv::Vec2f> dst;
	cv::perspectiveTransform(basePoints, dst, h);
	for (auto i = 0; i < dst.size(); i++) {
		mesh.setVertex(i, ofVec2f(dst[i][0], dst[i][1]));
	}

}

void ofxPlaneWarp::warpMode(bool value)
{
	isWarpMode = value;
	update();
}

void ofxPlaneWarp::mouseDragged(int x, int y, int button)
{
	if (selectedPointIndex >= 0) {
		if (selectedPointIndex < cornerPoints.size()) {
			cornerPoints[selectedPointIndex][0] = x;
			cornerPoints[selectedPointIndex][1] = y;
		}
		else {
			for (auto i = 0; i < cornerPoints.size(); i++) {
				cornerPoints[i][0] += x - preMousePosition.x;
				cornerPoints[i][1] += y - preMousePosition.y;
			}
		}
		update();
	}
}

void ofxPlaneWarp::mousePressed(int x, int y, int button)
{
	if (isWarpMode) {
		for (auto i = 0; i < cornerPoints.size(); i++) {
			if (ofDist(x, y, cornerPoints[i][0], cornerPoints[i][1]) < touchDistThreashold) {
				selectedPointIndex = i;
				break;
			}
		}
	}
}


void ofxPlaneWarp::mouseReleased(int x, int y, int button)
{
	update();
	selectedPointIndex = -1;

}

void ofxPlaneWarp::drawWireframe()
{
	mesh.drawWireframe();
	if (isWarpMode) {
		ofSetColor(0, 255, 0, 127);
		for (auto i = 0; i < cornerPoints.size(); i++) {
			ofDrawCircle(cornerPoints[i][0], cornerPoints[i][1], touchDistThreashold);
		}
	}
}
