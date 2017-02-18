#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "opencv.hpp"

class ofxPlaneWarp {
public:
	void draw(ofTexture& texture);
	void drawWireframe();
	void setup(float x,float y,float w,float h,int wSeg,int hSeg);
	void update();
	void warpMode(bool value);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

private:

	ofMesh mesh;
	float touchDistThreashold = 10;
	vector<cv::Vec2f> baseCornerPoints;
	vector<cv::Vec2f> basePoints;
	vector<cv::Vec2f> cornerPoints;
	ofVec2f preMousePosition;
	cv::Mat h;
	bool isWarpMode;
	int selectedPointIndex;
};