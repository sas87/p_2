#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofDisableAntiAliasing();

	start = false;
	isRunning = false;
	counter = 0;
	gene = 0;
	videc = false;
	pic = 0;

	gui.setup();
	gui.add(div_1.setup("d_1", 0.2f, 0.0f, 1.0f));
	gui.add(div_2.setup("d_2", 0.805f, 0.0f, 1.0f));
	gui.add(div_3.setup("d_3", 0.645f, 0.0f, 1.0f));

	box[0] = 80;  //x座標
	box[1] = 80;  //y座標
	box[2] = 512;  //x幅
	box[3] = 512;  //y幅

	ofBackground(200, 200, 200);

	/*world = {
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,true ,true ,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,true ,true ,true ,false,true ,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,true ,false,true ,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,true ,false,true ,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,true ,true ,true ,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,true ,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
	};   //{{行},{行},{行},...}*/

	world = vector<vector<float>>(256, vector<float>(256, 0.0f));
	block = vector<vector<bool>>(world.size(), vector<bool>(world[0].size(), false));
	blocks_n = vector<vector<int>>(world.size(), vector<int>(world[0].size(), 0));
	orbt = vector<vector<vector<float>>>(world.size(), vector<vector<float>>(world[0].size(), vector<float>(8, 0.0f)));

	for (size_t i = 0; i < (int)block.size() - 1; i++)
	{
		block[i][0] = true;
		block[i][world.size() - 1] = true;
	}
	for (size_t j = 0; j < (int)block.size() - 1; j++)
	{
		block[0][j] = true;
		block[world[0].size() - 1][j] = true;
	}

	n_w = world;
	n_b = block;
	vector<vector<bool>> acorn = {
	{ false,true ,false,false,false,false,false},
	{ false,false,false,true ,false,false,false},
	{ true ,true ,false,false,true ,true ,true }
	};
	vector<vector<bool>> glidergun = {
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,true ,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,true ,false  ,true ,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,true ,true   ,false,false,false,false,false  ,false,true ,true ,false,false  ,false,false,false,false,false  ,false,false,false,false,false,true ,true ,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,true ,false,false  ,false,true ,false,false,false  ,false,true ,true ,false,false  ,false,false,false,false,false  ,false,false,false,false,false,true ,true ,false },//38
	{ false,true ,true ,false,false  ,false,false,false,false,false  ,false,true ,false,false,false  ,false,false,true ,false,false  ,false,true ,true ,false,false  ,false,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,true ,true ,false,false  ,false,false,false,false,false  ,false,true ,false,false,false  ,true ,false,true ,true ,false  ,false,false,false,true ,false  ,true ,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,true ,false,false,false  ,false,false,true ,false,false  ,false,false,false,false,false  ,true ,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,true ,false,false  ,false,true ,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,true ,true   ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false,false,false,false },//38
	{ false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false  ,false,false,false,false,false,false,false,false }//38
	};

	vector<vector<float>> glidergun_f = {
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,1.0f ,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,1.0f ,0.1f  ,1.0f ,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,1.0f ,1.0f   ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,1.0f ,1.0f ,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,1.0f ,1.0f ,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,1.0f ,0.1f,0.1f  ,0.1f,1.0f ,0.1f,0.1f,0.1f  ,0.1f,1.0f ,1.0f ,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,1.0f ,1.0f ,0.1f },//38
{ 0.1f,1.0f ,1.0f ,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,1.0f ,0.1f,0.1f,0.1f  ,0.1f,0.1f,1.0f ,0.1f,0.1f  ,0.1f,1.0f ,1.0f ,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,1.0f ,1.0f ,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,1.0f ,0.1f,0.1f,0.1f  ,1.0f ,0.1f,1.0f ,1.0f ,0.1f  ,0.1f,0.1f,0.1f,1.0f ,0.1f  ,1.0f ,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,1.0f ,0.1f,0.1f,0.1f  ,0.1f,0.1f,1.0f ,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,1.0f ,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,1.0f ,0.1f,0.1f  ,0.1f,1.0f ,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,1.0f ,1.0f   ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f },//38
{ 0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f  ,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f }//38
	};

	vector<vector<bool>> sam1 = {
	{ false,false,true ,false,true ,false },
	{ false,true ,true ,false,true ,false },
	{ true ,false,false,false,false,false },
	{ false,true ,true ,false,false,true  },
	{ false,false,true ,false,true ,false }
	};

	vector<vector<float>> pre1 = { {1.0f} };
	//vector<vector<bool>> sample1(7, vector<bool>(7, true));
	addVecter(pre1);

	for (size_t i = 0 + 1; i < (int)world.size() - 1; i++)
	{
		for (size_t j = 0 + 1; j < (int)world[i].size() - 1; j++)
		{
			//world[i][j] = abs(ofRandomf());
		}
	}

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {
	counter++;
	if (counter > 1000)counter = 0;
	//if (start && (world != pre_w))
	if (isRunning)
	{
		//if (counter % 2 == 0)
		geneChange();
		gene++;
		/**/
		if (pic < 140)
		{
			//img.grabScreen(0, 0, 2*box[0]+box[2], 2*box[1] + box[3]);
			//img.save("002/"+ofToString(pic)+".png");
			//pic++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(200, 200, 200);
	//ofDrawRectangle(box[0] - 5, box[1] - 5, box[2] + 10, box[3] + 10);
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

				ofSetColor(255 * world[i][j], 255 * world[i][j], 255 * world[i][j]);
				//if (world[i][j] > div_3)ofSetColor(255,0,0);
				if (block[i][j])ofSetColor(200, 200, 200);
				if (i == mY && j == mX)ofSetColor(255, 0, 0);

				//ofSetColor(255* i / (int)world.size(), 255 * j / (int)world[i].size(), 128);                           //Debug
				ofDrawRectangle(px, py, box[2] / (int)world[i].size(), box[3] / (int)world[i].size());

				//ofSetColor(128, 128, 128);                                                                             //Debug
				//ofDrawBitmapString(ofToString(i) + "," + ofToString(j), px, py+10);                                    //Debug
			}
		}/**/
	}
	ofSetColor(0, 0, 0);

	ofDrawBitmapString(
		(string)""
		+ "isRunning: " + ofToString(isRunning) + "\r\n"
		+ "g:" + ofToString(gene) + "\r\n"
		+ "\r\n"
		+ "m:" + ofToString(world[mY][mX]) + "\r\n",
		box[0] + box[2] + 50, box[1] + 60);
	ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", box[0] + box[2] + 50, box[1] + 15);

	{
	}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		world = n_w;
		for (size_t i = 0 + 1; i < (int)world.size() - 1; i++)
		{
			for (size_t j = 0 + 1; j < (int)world[i].size() - 1; j++)
			{
				world[i][j] = abs(ofRandomf());
			}
		}
		orbt = vector<vector<vector<float>>>(world.size(), vector<vector<float>>(world[0].size(), vector<float>(100, 0.0f)));
		gene = 0;
		isRunning = false;
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

void ofApp::geneChange()
{
	pre_w = world;
	world = n_w;

	for (size_t i = 0 + 1; i < (int)pre_w.size() - 1; i++)
	{
		for (size_t j = 0 + 1; j < (int)pre_w[i].size() - 1; j++)
		{
			orbt[i][j][0] = pre_w[i][j];
			for (size_t k = 0; k < orbt[0][0].size() - 1; k++)
			{
				orbt[i][j][k] = orbt[i][j][k + 1];
			}

			if (!block[i][j]) {
				float alpha = 0.9f;
				float pw = pre_w[i][j];
				if (pre_w[i][j] > div_3)
				{
					alpha = div_1;
				}
				else alpha = div_2;

				if (alpha > 1.0f)
				{
					alpha = 1.0;
				}
				if (alpha < 0)
				{
					alpha = 0.0f;
				}

				int bc = 4;
				if (!block[i][j + 1]) {
					world[i][j + 1] += pw * (1 - alpha)*0.25f;
					bc--;
				}
				if (!block[i][j - 1]) {
					world[i][j - 1] += pw * (1 - alpha)*0.25f;
					bc--;
				}
				if (!block[i + 1][j]) {
					world[i + 1][j] += pw * (1 - alpha)*0.25f;
					bc--;
				}
				if (!block[i - 1][j]) {
					world[i - 1][j] += pw * (1 - alpha)*0.25f;
					bc--;
				}
				if (!block[i][j]) world[i][j] += pw * (alpha + (1 - alpha)*0.25f*bc);

				blocks_n[i][j] = pw * (alpha + (1 - alpha)*0.25f*bc) * 10;
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

ofVec3f ofApp::FlotoCol(float p)
{
	//p *= 0.1f;
	//p = 1.0f - p;
	p *= 80;
	if (p <= 1 && p >= 0)
	{
		int r = 128 + 127 * sin(2.0f*p*PI / 2.0f - PI / 2.0f);
		int g = 88 + 94 * sin(2.0f*p*PI - PI / 2.0f);
		int b = 128 + 64 * sin(2.0f*p*PI - PI / 4.0f);
		return ofVec3f(r, g, b);/*
		int r = p * 255;
		int g = p * 255;
		int b = p*255;
		return ofVec3f(r, g, b);*/
	}
	else return ofVec3f(0, 0, 0);
}