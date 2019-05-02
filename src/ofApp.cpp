#include "ofApp.h"

#define SIZE 256
//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableAntiAliasing();
	isRunning = false;
	counter = 0;
	gene = 0;
	videc = false;
	pic = 0;
	

	gui.setup();

	gui.add(al.setup("alpha",0.805f, 0.0f, 1.0f));
	gui.add(bt.setup("beta", 0.2f, 0.0f, 1.0f));
	gui.add(c0.setup("c", 0.645f, 0.0f, 1.0f));
	gui.add(max.setup("max", 1.0f, 0.0f, 5.0f));
	gui.add(min.setup("min", 0.0f, 0.0f, 5.0f));
	
	box[0] = 50;  //x座標
	box[1] = 10;  //y座標
	box[2] = SIZE*6;  //x幅
	box[3] = SIZE*3;  //y幅

	ofBackground(200, 200, 200);

	col = new gra();

	world = vector<vector<float>>(SIZE, vector<float>(SIZE*2, 0.0f));
	block = vector<vector<bool>>(world.size(), vector<bool>(world[0].size(), false));
	blocks_n = vector<vector<int>>(world.size(), vector<int>(world[0].size(), 0));
	orbt = vector<vector<vector<float>>>(world.size(), vector<vector<float>>(world[0].size(), vector<float>(8, 0.0f)));
	n_w = world;
	n_b = block;

	start();

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {
	counter++;
	if (counter > 1000)counter = 0;
	if (isRunning)
	{
		geneChange();
		col->max = max;
		col->min = min;
		gene++;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(200, 200, 200);
	ofSetColor(0, 0, 0);
	int width = (int)(box[2] * 1.0f / world[0].size());
	int height = (int)(box[3] * 1.0f / world.size());

	int mX = (int)((mouseX - box[0]) *1.0f / width);
	int mY = (int)((mouseY - box[1]) *1.0f / height);
	if (mX < 0 || mX >= world[0].size())mX = 0;
	if (mY < 0 || mY >= world.size())mY = 0;

	{
		for (size_t i = 0; i < (int)world.size(); i++)
		{
			int py = box[1] + i * box[3] / (int)world.size();                       //行

			for (size_t j = 0; j < (int)world[0].size(); j++)
			{
				int px = box[0] + j * box[2] / (int)world[0].size();               //列

				ofSetColor(col->flotocol(world[i][j]));
				//ofSetColor(world[i][j] * 255, world[i][j] * 255, world[i][j] * 255);
				if (j == mX && i == mY)ofSetColor(255, 0, 0);
				ofDrawRectangle(px, py, box[2] / (int)world[0].size(), box[3] / (int)world.size());
			}
		}
	}

	col->draw(box[0] - 15, box[1] + box[3]/2);

	ofSetColor(0, 0, 0);
	ofDrawBitmapString(
		(string)""
		+ "isRunning: " + ofToString(isRunning) + "\r\n"
		+ "g:" + ofToString(gene) + "\r\n"
		+ "\r\n"
		+ "m:" + ofToString(world[mY][mX]) + "\r\n"
		+ "V_M:" + ofToString(c0*(al*1.0f/bt)) + "\r\n"
		+ "v_m:" + ofToString(c0 * (bt * 1.0f / al)) + "\r\n",
		box[0] + box[2] + 50, box[1] + 60);
	ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", box[0] + box[2] + 50, box[1] + 15);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		ofApp::start();
	};

	if (key == 'x') {
		videc = true;
	}
	if (key == 'z') {
		isRunning = !isRunning;
	}
	if (key == 'c') {
		block = n_b;
	}
	if (key == 'v') {
		isRunning = true;
		ofApp::update();
		isRunning = false;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (button == 0) {
		int width = (int)(box[2] * 1.0f / world[0].size());
		int height = (int)(box[3] * 1.0f / world.size());
		int mX = (int)((x - box[0]) *1.0f / width);
		int mY = (int)((y - box[1]) *1.0f / height);
		if (mX < 0 || mX >= world[0].size())mX = 0;
		if (mY < 0 || mY >= world.size())mY = 0;
		block[mY][mX] = true;
	}
	if (button == 2) {
		int width = (int)(box[2] * 1.0f / world[0].size());
		int height = (int)(box[3] * 1.0f / world.size());
		int mX = (int)((x - box[0]) *1.0f / width);
		int mY = (int)((y - box[1]) *1.0f / height);
		if (mX < 0 || mX >= world[0].size())mX = 0;
		if (mY < 0 || mY >= world.size())mY = 0;
		block[mY][mX] = false;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::mouseClicked(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

float alpha, pw;
void ofApp::geneChange()
{
	pre_w = world;
	world = n_w;

	int ie = (int)pre_w.size();
	int je = (int)pre_w[0].size();

	for (size_t i = 0; i < ie; i++)
	{
		for (size_t j = 0; j < je; j++)
		{
			if (true) {			
				pw = pre_w[i][j];

				if (pw > c0)alpha = bt;
				else alpha = al;
				
				world[i][(j + 1) % je] += pw * (1 - alpha) / 4.0f;
				world[i][(j - 1 + je) % je] += pw * (1 - alpha) / 4.0f;
				world[(i + 1) % ie][j] += pw * (1 - alpha) / 4.0f;
				world[(i - 1 + ie) % ie][j] += pw * (1 - alpha) / 4.0f;
				world[i][j] += pw * alpha;
			}
		}
	}
}

void ofApp::addVecter(vector<vector<float>> vv1, int x, int y)
{
	if (x < 0 || y < 0 || y + (int)vv1.size() > world.size() || x + (int)vv1.size() > world[0].size())
	{
		return;
	}
	for (size_t i = y; i < y + (int)vv1.size(); i++)
	{
		for (size_t j = x; j < x + (int)vv1[0].size(); j++)
		{
			world[i][j] += vv1[i - y][j - x];
		}
	}
}

void ofApp::addVecter(vector<vector<float>> vv1)
{
	int y = ((int)world.size() - vv1.size()) / 2;
	int x = ((int)world[0].size() - vv1[0].size()) / 2;

	ofApp::addVecter(vv1, x, y);
}

void ofApp::start()
{
	world = n_w;
	float min = al;// c0* bt* 1.0f / al;
	float max = bt;// c0* al* 1.0f / bt;
	for (auto&& vy : world) {
		for (auto&& v : vy) {
			v = abs(ofRandomf()) * (max - min) + min;
		}
	}
	orbt = vector<vector<vector<float>>>(world.size(), vector<vector<float>>(world[0].size(), vector<float>(100, 0.0f)));
	gene = 0;
	isRunning = false;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

ofColor gra::flotocol(float p)
{
	p = (p - min) * 1.0f / (max - min);

	if (p <= 1 && p >= 0)
	{
		int r, g, b;
		if (p >= 2 / 3.0f)
		{
			r = 255;
			g = 255 - 255 * (3 * p - 2);
			b = 0;
		}
		else if (p >= 1 / 3.0f)
		{
			r = 255 * (3 * p - 1);
			g = 255;
			b = 255 - 255 * (3 * p - 1);
		}
		else
		{
			r = 0;
			g = 255 * (3 * p);
			b = 255;
		}

		return ofColor(r, g, b);
	}
	else if (p <= min)
	{
		return ofColor(0, 0, 0);
	}
	else
	{
		return ofColor(255, 255, 255);
	}
}

gra::gra()
{
	min = 0.0f;
	max = 1.0f;

	width = 4;
	height = 256;
	rep = 256;
}

void gra::draw(int x, int y)
{
	for (size_t i = 0; i < rep; i++)
	{
		float cl = (i * 1.0f / rep);
		ofSetColor(flotocol(cl * (max - min) + min));
		ofDrawRectangle(x, (int)(cl * height + y - (height / 2)), width, (int)height/rep);
	}
	ofSetColor(0, 0, 0);
	//ofDrawBitmapString(ofToString(min), x, y - height / 2);
}
