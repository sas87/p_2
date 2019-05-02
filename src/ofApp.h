#pragma once
#include "ofxGui.h"
#include "ofMain.h"

class gra {
public:

	gra();
	ofColor flotocol(float p);
	void draw(int x, int y);
	int height,width,rep;
	float min, max;
};

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseClicked(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	int counter;
	bool isRunning;
	int box[4];
	int gene;

	vector<vector<float>> world;
	vector<vector<float>> pre_w;
	vector<vector<float>> n_w;
	vector<vector<vector<float>>> orbt;
	vector<vector<bool>> block;
	vector<vector<bool>> n_b;
	vector<vector<int>> blocks_n;
	void geneChange();
	void addVecter(vector<vector<float>> vv1, int x, int y);
	void addVecter(vector<vector<float>> vv1);
	void start();

	ofImage     img;
	bool videc;
	int pic;

	ofxFloatSlider al;
	ofxFloatSlider bt;
	ofxFloatSlider c0;

	ofxFloatSlider max;
	ofxFloatSlider min;

	ofxPanel gui;
	gra* col;
};


