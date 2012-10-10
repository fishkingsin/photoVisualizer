/**
*
* OFDevCon Example Code Sprint
* Quaternion Example for plotting latitude and longitude onto a sphere
*
* Created by James George on 2/23/2012
*/

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetFrameRate(30);
	ofEnableAlphaBlending();
	ofNoFill();

	// create little objects for each city. 
	// A Lat/Lon like this: 
	// Lewiston, Idaho 	W 46 24' N 117 2'
	// This translate to angles and degrees (1 degree = 1/60. of an angle)
	// West and South are negative values

	// here is a list of big cities and their positions
	// http://www.infoplease.com/ipa/A0001796.html
	ofDirectory dir;

	dir.allowExt("tif");

	{
		int num = dir.listDir("/training");
		cout << "num faces :" << num << endl;
		float step = (360.0f/num*1.0f)*10;
		for(int i = 0 ; i < num ; i++)
		{
			string file_name = dir.getName(i);
			string name = file_name.substr(0,file_name.length()-4);
			Face face = {name ,((i+1)/(360/step))*step-90, i*step, new ofImage(dir.getPath(i))};
			//Face face = {name ,((i+1)/(360/step))*step-90, i*step, new ofImage(dir.getPath(i))}; // sami sprial
			faces.push_back( face );
		}
	}
	/*City newyork = { "new york", 40+47/60., -73 + 58/60. , new ofImage("new york.jpg")};
	City tokyo = { "tokyo", 35 + 40./60, 139 + 45/60.  , new ofImage("tokyo.jpg")};
	City london = { "london", 51 + 32/60., -5./60.  , new ofImage("london.jpg")};
	City shanghai = { "shanghai", 31 + 10/60., 121 + 28/60.  , new ofImage("shanghai.jpg")};
	City buenosaires = { "buenos aires", -34 + 35/60., -58 + 22/60. , new ofImage("buenos aires.jpg") };
	City melbourne = { "melbourne" , -37 + 47/60., 144 + 58/60.  , new ofImage("melbourne.jpg")};	
	City detroit = { "detroit", 42 + 19/60., -83 + 2 / 60.  , new ofImage("detroit.jpg")};

	cities.push_back( newyork );
	cities.push_back( tokyo );
	cities.push_back( london );
	cities.push_back( shanghai );
	cities.push_back( buenosaires );
	cities.push_back( melbourne );
	cities.push_back( detroit );*/
	glEnable(GL_DEPTH_TEST);
	mode = '1';
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	if(mode=='1')
	{
		ofPushMatrix();

		//translate so that the center of the screen is 0,0
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofSetColor(255, 255, 255, 20);

		//draw a translucent wireframe sphere (ofNoFill() is on)
		ofPushMatrix();
		//add an extra spin at the rate of 1 degree per frame
		float rotSpeed = ofGetFrameNum()*0.8;
		ofRotate(rotSpeed, 0, 1, 0);
		ofSphere(0, 0, 0, 300);
		ofPopMatrix();

		ofSetColor(255);	
		for(int i = 0; i < faces.size(); i++){

			//three rotations
			//two to represent the latitude and lontitude of the city
			//a third so that it spins along with the spinning sphere 
			ofQuaternion latRot, longRot, spinQuat;
			latRot.makeRotate(faces[i].latitude, 1, 0, 0);
			longRot.makeRotate(faces[i].longitude, 0, 1, 0);
			spinQuat.makeRotate(rotSpeed, 0, 1, 0);




			//our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
			ofVec3f center = ofVec3f(0,0,300);
			//multiplying a quat with another quat combines their rotations into one quat
			//multiplying a quat to a vector applies the quat's rotation to that vector
			//so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
			ofVec3f worldPoint = latRot * longRot * spinQuat * center;


			//draw it and label it
			ofLine(ofVec3f(0,0,0), worldPoint);

			//set the bitmap text mode billboard so the points show up correctly in 3d
			ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);

			glPushMatrix();
			float angleX = 0;
			float angleY = 0;
			float angleZ = 0;
			
			
			glTranslatef(worldPoint.x,worldPoint.y,worldPoint.z);
			ofVec3f c = worldPoint.getNormalized();
			
			ofVec3f v;
			float rX;
			float rY;
			longRot.getRotate(rY,v);
			latRot.getRotate(rX,v);
			glScalef(0.2,0.2,1);
			glRotatef(rX,1,0,0);
			glRotatef(rY,0,1,0);
			glTranslatef(-faces[i].img->getWidth()*0.5,-faces[i].img->getHeight()*0.5,0);
			faces[i].img->draw(0,0);
			glPopMatrix();

			//ofDrawBitmapString(faces[i].name, worldPoint );
		}
		ofPopMatrix();
	}
	else
	{
		int iwidth = ofGetWidth()/128;
		for(int i = 0; i < faces.size(); i++){
			float x = i%iwidth*128;
			float y = i/iwidth*128;
			glPushMatrix();
			glTranslatef(x,y,-1);
			//glScalef(0.1,0.1,1);
			faces[i].img->draw(0,0,128,128);
			glPopMatrix();

			ofDrawBitmapString(faces[i].name, x,y );
		}
	}

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	mode = key;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}